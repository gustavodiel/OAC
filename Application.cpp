/************************************************************************/
/* File: Application.cpp                                                */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

/* Basic Includes */
#include "stdafx.h"
#include "Application.h"

/* Standard Includes */
#include <Windows.h>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

/* OpenGL Includes */
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <gl/gl.h>

/* Util Includes */
#include "Shader.h"
#include "OBJLoader.h"
#include "Controller.h"
#include "TextureLoader.h"
#include "QuatUtils.h"
#include "Constants.h"
#include "ParticleSystem.h"
#include "DebugDraw.h"
#include "Camera.h"
#include "Light.h"
#include "SkyBox.h"
#include "BillBoard.h"
#include "BulletHandler.h"
#include "Keyboard.h"


/* Objects Includes */
#include "Entity.h"
#include "Model.h"
#include "Cloth.h"


/* Steering Behaviours */
#include "Vehicle.h"


/* GLM Includes */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>


using namespace glm;

/* Globals */
GLFWwindow* window;

extern Shader* ptrShader = new Shader();
extern Controller* ptrController = new Controller();
extern QuatUtils* ptrQuatUtils = new QuatUtils();
extern TextureLoader* ptrTextureLoader = new TextureLoader();
extern OBJLoader* ptrObjLoader = new OBJLoader();
extern BulletHandler* ptrBulletHandler = new BulletHandler(vec3(0, -9.8, 0));
extern DebugDraw* ptrDebugger = new DebugDraw();


/**
\brief Construtor default para a classe Application
*/
Application::Application(unsigned int width, unsigned int height, string strAppName) :
	strCurrentFPS("Trab OAC - Gustavo Diel"), dCounterTimer(0.0), uiFrames(0), dTotalTime(0.0), uiFrameRate(0)
{
	this->strAppName = strAppName;
	this->iWindowWidth = width;
	this->iWindowHeight = height;

	this->StartWindow();

}

/**
\brief Desaloca todos os membros dinamicos utilizados na classe Application
*/
Application::~Application()
{
	for (vector<Entity*>::iterator pointer = this->listOfEntities.begin(); pointer != this->listOfEntities.end(); pointer++)
		delete (*pointer);
}

void Application::AddParticleSystem(ParticleSystem* ptrParticleSystem)
{
	this->listOfParticleSys.push_back(ptrParticleSystem);
}

void Application::OnRenderParticle()
{
	for (vector<ParticleSystem*>::iterator particleSystem = this->listOfParticleSys.begin(); particleSystem != this->listOfParticleSys.end(); particleSystem++)
		if (*particleSystem)
			(*particleSystem)->OnRender();
}

/**
\brief Executa o loop principal da aplicacao IDS
\param dElapsedTime tempo transcorrido (em milisegundos) entre duas chamadas consecutivas da funcao
\return int flag que indica sucesso ou falha na execucao
*/
int Application::Execute(double dElapsedTime)
{
	this->CalculateFPS(dElapsedTime);

	ptrBulletHandler->OnUpdate(dElapsedTime);

	for (vector<Entity*>::iterator entity = this->listOfEntities.begin(); entity != this->listOfEntities.end();) {
		if (*entity) {
			if ((*entity)->getTranslate().y < -1 && (*entity) != ptrcMainCamera && (*entity)->bDeletable) {
				ptrBulletHandler->GetWorld()->removeRigidBody((*entity)->getRigidBody());
				listOfEntities.erase(entity);
				continue;
			}
			else {
				(*entity)->OnLoop(dElapsedTime);
			}
		}
		entity++;
	}

	for (vector<Entity2D*>::iterator billboard = this->listOfBillboards.begin(); billboard != this->listOfBillboards.end(); billboard++)
		if (*billboard)
			(*billboard)->OnLoop(dElapsedTime);

	for (vector<Function>::iterator itFunc = this->listOfFunctions.begin(); itFunc != this->listOfFunctions.end();) {
		Function f = (*itFunc);
		if (f.dTimeToExecute <= this->dTotalTime) {
			f.fFuncToExecute(dElapsedTime);
			listOfFunctions.erase(itFunc);
		}
		else {
			itFunc++;
		}

	}

	int numPars = this->listOfParticleSys.size();
	for (int i = 0; i < numPars; ++i) {
		ParticleSystem* particleSystem = this->listOfParticleSys[i];
		particleSystem->OnLoop(dElapsedTime);
	}

	return 1;
}

void Application::DebugDraw()
{
	glLineWidth(2.5);
	glPushMatrix();
	glTranslated(0, 0, 0);
	glColor3f(1.0, 0.0, 0.0);
	for (auto ponto : pontos) {
		glBegin(GL_LINES);
			glVertex3f(ponto.from.x, ponto.from.y, ponto.from.z);
			glVertex3f(ponto.to.x, ponto.to.y, ponto.to.z);
		glEnd();
	}
	glPopMatrix();
	pontos.clear();
}

/**
\brief Efetua o calculo do FPS (Frames per Second) disponivel
\param dElapsedTime tempo transcorrido entre duas chamadas consecutivas da funcao
*/
void Application::CalculateFPS(double dElapsedTime)
{
	this->dCounterTimer += dElapsedTime;
	this->dTotalTime += dElapsedTime;
	uiFrames++;

	//char strFPS[30];

	//sprintf(strFPS, "Trab OAC - %d FPS %.3f s", this->uiFrameRate, this->dTotalTime);

	//glfwSetWindowTitle(ptrWindow, strFPS);

	if (this->dCounterTimer >= 1.0) // 1 segundo transcorrido?
	{
		this->uiFrameRate = this->uiFrames;
	//	this->strCurrentFPS = strFPS;
		this->uiFrames = 0;
		this->dCounterTimer = 0.0;
	}
}

/**
\brief Metodo responsavel por desenhar cada frame da aplicacao
*/
void Application::OnRender()
{
	for (vector<Entity*>::iterator entity = this->listOfEntities.begin(); entity != this->listOfEntities.end(); entity++) {
		(*entity)->OnRender(this->m4Unitaria);
	}
}

/**
\brief Metodo responsavel por desenhar as sombras na textura de sombra
*/
void Application::OnPreRender()
{
	for (vector<Entity*>::iterator entity = this->listOfEntities.begin(); entity != this->listOfEntities.end(); entity++)
		(*entity)->OnPreRender(this->m4Unitaria);
}

void Application::AddFunction(Function func)
{
	this->listOfFunctions.push_back(func);
}

/**
\brief Metodo responsavel por desenhar cada frame da aplicacao
*/
void Application::OnRenderBillboard()
{
	for (vector<Entity2D*>::iterator entity = this->listOfBillboards.begin(); entity != this->listOfBillboards.end(); entity++) {
		(*entity)->OnRender(this->m4Unitaria);
	}
}

/**
\brief Metodo responsavel por desenhar as sombras na textura de sombra
*/
void Application::OnPreRenderBillboard()
{
	for (vector<Entity2D*>::iterator entity = this->listOfBillboards.begin(); entity != this->listOfBillboards.end(); entity++)
		(*entity)->OnPreRender(this->m4Unitaria);
}

/**
\brief Adiciona uma nova entidade renderizavel a cena sendo manipulada
\param ptrEnt ponteiro para a nova entidade a ser adicionada a cena
*/
void Application::AddEntity(Entity* ptrEnt)
{
	this->listOfEntities.push_back(ptrEnt);
}

/**
\brief Adiciona uma nova bilboard renderizavel a cena sendo manipulada
\param ptrEnt ponteiro para a nova bilboard a ser adicionada a cena
*/
void Application::AddBillboard(Entity2D* ptrBillboard)
{
	this->listOfBillboards.push_back(ptrBillboard);
}

/**
\brief Altera uma dada entidade pertencente a cena sendo manipulada
\param ptrEnt ponteiro para a nova entidade a ser adicionada a cena
\param uiIndex posicao da entidade na lista de entidades da cena
\return flag que indica se houve sucesso na operacao
*/
bool Application::SetEntity(Entity* ptrEnt, unsigned int uiIndex)
{
	if (uiIndex < this->listOfEntities.size())
	{
		this->listOfEntities[uiIndex] = ptrEnt;
		return true;
	}
	return false;
}
/**
\brief Retorna uma dada entidade da cena sendo manipulada
\param uiIndex posicao da entidade na lista de entidades da cena a ser retornada
\return ponteiro para a dade entidade ou NULL caso indice invalido
*/
Entity* Application::GetEntity(unsigned int uiIndex)
{
	if (uiIndex < this->listOfEntities.size())
	{
		return this->listOfEntities[uiIndex];
	}
	return NULL;
}

void Application::AddTimerFunction(function<void(double)> fFuncToExecute, double dTimeToExecute)
{
	Function timedFunction = { fFuncToExecute, dTimeToExecute };
	this->AddFunction(timedFunction);
}

int Application::getEntityCount()
{
	return listOfEntities.size();
}

/**
\brief Gera a janela visivel ao usuário e inicia algumas variaveis
*/
void Application::StartWindow() {
	// Initialise GLFW
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		exit(-1);
	}

	glfwWindowHint(GLFW_SAMPLES, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__ // To make MacOS happy :D
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
#endif // __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);


	// Open a window and create its OpenGL context
	//ptrWindow = glfwCreateWindow(iWindowWidth, iWindowHeight, "Trab OAC - x FPS", glfwGetPrimaryMonitor(), NULL);
	ptrWindow = glfwCreateWindow(iWindowWidth, iWindowHeight, "Trab OAC - x FPS", glfwGetPrimaryMonitor(), NULL);
	if (ptrWindow == NULL) {
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible.\n");
		getchar();
		glfwTerminate();
		exit(-1);
	}
	glfwMakeContextCurrent(ptrWindow);
	// We would expect width and height to be what we set

	// But on MacOS X with a retina screen it'll be twice the size, so we get the actual framebuffer size:
	glfwGetFramebufferSize(ptrWindow, &iWindowWidth, &iWindowHeight);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		exit(-1);
	}

}

/**
\brief Gera a janela visivel ao usuário e inicia algumas variaveis
*/
void Application::InitApplication() {

	printf("Starting Application\n");		/* Damos um bem-vindo :3 */

	int shadowMapSize = 1024 * 8;			/* Tamanho do mapa de sombras */

	/* Envia algumas informacoes para o Controller para ele poder fazer as projecoes */
	ptrController->window = ptrWindow;
	ptrController->windowHeight = iWindowHeight;
	ptrController->windowWidth = iWindowWidth;

	/* Configura o GLFW para poder apertar mais de uma tecla por vez e desativar o mouse */
	glfwSetInputMode(ptrWindow, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(ptrWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	/* Set the mouse at the center of the screen */
	glfwPollEvents();
	glfwSetCursorPos(ptrWindow, this->iWindowWidth / 2, this->iWindowHeight / 2);

	/* Cor do fundo. Nao utilizado por causa do SkyBox */
	glClearColor(0.1f, 0.3f, 0.9f, 0.0f);

	/* Ativa teste de profundidade */
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glLineWidth(20.0f);



	/* Vamos enviar todos os vertices parar esse cara que fica no shader */
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	/************************************************************************/
	/* Comeca parte de carregar o shader de sombra                          */
	/************************************************************************/

	/* Carrega o shader */
	uiShadowProgramId = ptrShader->LoadShaders("shaders/DepthRTT.vertexshader", "shaders/DepthRTT.fragmentshader");
	uiDepthMatrixId = glGetUniformLocation(uiShadowProgramId, "depthMVP");

	/* Define buffer para ele */
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	/* A sombra precisa de uma textura para ser aplicada e entao desenhada */
	glGenTextures(1, &this->uiDepthTextureId);
	glBindTexture(GL_TEXTURE_2D, this->uiDepthTextureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, shadowMapSize, shadowMapSize, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, this->uiDepthTextureId, 0);

	/* Nao queremos desenhar na tela, apenas no buffer */
	glDrawBuffer(GL_NONE);

	/* Evita coisas bizaras */
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		exit(-1);

	/************************************************************************/
	/* Comeca parte do shader principal                                     */
	/************************************************************************/

	/* Carrega o shader */
	this->uiProgramId = ptrShader->LoadShaders("shaders/ShadowMapping.vertexshader", "shaders/ShadowMapping.fragmentshader");

	/* Esta parte server para pegar o lugar da memoria onde as variaveis de entrada do shader estao 
	   e entao podemos nos "conversar" com o shader	*/
	this->uiTextureId = glGetUniformLocation(this->uiProgramId, "myTextureSampler");
	this->uiAmbientMaterial = glGetUniformLocation(this->uiProgramId, "ambientColor");
	this->uiSpecularMaterial = glGetUniformLocation(this->uiProgramId, "specularColor");
	this->uiMVPMatrixId = glGetUniformLocation(this->uiProgramId, "MVP");
	this->uiViewMatrixId = glGetUniformLocation(this->uiProgramId, "V");
	this->uiModelMatrixId = glGetUniformLocation(this->uiProgramId, "M");
	this->uiDepthBiasId = glGetUniformLocation(this->uiProgramId, "DepthBiasMVP");
	this->uiShadowMapId = glGetUniformLocation(this->uiProgramId, "shadowMap");
	this->uiLightDirectionId = glGetUniformLocation(this->uiProgramId, "LightInvDirection_worldspace");


	/************************************************************************/
	/* Skybox                                                               */
	/************************************************************************/
	SkyBox* skybox = new SkyBox();
	skybox->Initialize();

	/************************************************************************/
	/* Billboard                                                            */
	/************************************************************************/

	/* Carrega Shader */
	this->uiBillboardProgramId = ptrShader->LoadShaders("shaders/Billboard.vertexshader", "shaders/Billboard.fragmentshader");

	/* Pega a posicao das variaveis no shader */
	this->uiBillboardCameraRightId = glGetUniformLocation(this->uiBillboardProgramId, "CameraRight_worldspace");
	this->uiBillboardCameraUpId = glGetUniformLocation(this->uiBillboardProgramId, "CameraUp_worldspace");
	this->uiBillboardViewProjMatrixId = glGetUniformLocation(this->uiBillboardProgramId, "VP");
	this->uiBillboardPositionId = glGetUniformLocation(this->uiBillboardProgramId, "BillboardPos");
	this->uiBillboardSizeId = glGetUniformLocation(this->uiBillboardProgramId, "BillboardSize");
	this->uiBillboardStatusId = glGetUniformLocation(this->uiBillboardProgramId, "Status");
	this->uiBillboardTextureId = glGetUniformLocation(this->uiBillboardProgramId, "myTextureSampler");

	/************************************************************************/
	/* Particles                                                            */
	/************************************************************************/

	/* Carrega Shader */
	this->uiParticleProgramId = ptrShader->LoadShaders("shaders/Particle.vertexshader", "shaders/Particle.fragmentshader");

	/* Pega a posicao das variaveis no shader */
	this->uiParticleCameraRightWorldspaceId = glGetUniformLocation(this->uiParticleProgramId, "CameraRight_worldspace");
	this->uiParticleCameraUpWorldspaceId = glGetUniformLocation(this->uiParticleProgramId, "CameraUp_worldspace");
	this->uiParticleViewProjMatrixId = glGetUniformLocation(this->uiParticleProgramId, "VP");
	this->uiParticleTextureId = glGetUniformLocation(this->uiParticleProgramId, "myTextureSampler");

	/************************************************************************/
	/* Prepara para desenhar                                                */
	/************************************************************************/


	/* Para mover a luz em circulos. :3 */
	double posLightx = 0;
	double posLightz = 0;
	double angle = 0;
	double lightDist = 32;

	/* Descomente abaixo para ativar wireframe */
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/* Ativa Cull Face */
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	/* Comecamos a contar o tempo */
	double lastFrame = glfwGetTime();

	Keyboard* keyboard = new Keyboard();

	int n = 7;
	int i = 0;

	m4DepthProjection = glm::ortho<float>(-32, 32, -32, 32, -32, 20);

	/* Main Loop \m/ */
	do {

		keyboard->OnProcessEvent();

		/* Calcula a diferenca de tempo */
		GLfloat currentFrame = glfwGetTime();
		double elapsedTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
	
		/* Atualiza tudo */
		this->Execute(elapsedTime);

		/* Calcula as matrizes de projecao e view. O if e caso a camera nao tenha alvo, dai o mouse que controla */
		if (ptraCameraTarget) {
			if (this->ptrcMainCamera) {
				//ptrController->computeMatricesFromInputs(elapsedTime, new vec3(this->target->getTranslate()), new vec3(this->target->getTranslate() + this->camera->getTranslate()));
				// + vec3(0, 0.65, 0)
				vec3 sum = (this->ptraCameraTarget->getTranslate() + vec3(0, 1, -5));
				vec3* newVec = new vec3(sum.x, sum.y, sum.z);
				ptrController->computeMatricesFromInputs(elapsedTime, new vec3(this->ptraCameraTarget->GetWorldPosition() + vec3(0, 0.5, 0)), newVec);
			}
			else
				ptrController->computeMatricesFromInputs(elapsedTime, new vec3(this->ptraCameraTarget->GetWorldPosition()), this->ptrv3CameraPos);
		}
		else {
			ptrController->computeMatricesFromInputs(elapsedTime, this->ptrv3LookAtPos, this->ptrv3CameraPos);
		}
		
		/* Begin the shadow */
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
		glViewport(0, 0, shadowMapSize, shadowMapSize);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/* Ativa o shader */
		glUseProgram(uiShadowProgramId);

		if (this->ptrlMainLight) {
			v3LightDirection = this->ptrlMainLight->getTranslate();
		}
		else {
			posLightx = lightDist * sin(angle);
			posLightz = lightDist * cos(angle);
			angle += 0.1 * elapsedTime;
			v3LightDirection = glm::vec3(posLightx, 1, posLightz);
		}
		m4DepthView = glm::lookAt(v3LightDirection, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

		/************************************************************************/
		/* Desenha Sombra                                                       */
		/************************************************************************/
		this->OnPreRender();
		this->OnPreRenderBillboard();

		/* Limpamos o buffer, mas guardamos para usar depois */
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, this->iWindowWidth, this->iWindowHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(0);


		/************************************************************************/
		/* Desenha Skybox                                                       */
		/************************************************************************/
		glDepthMask(GL_FALSE); // Sem teste de Depth
		skybox->OnRender();
		glDepthMask(GL_TRUE);

		/************************************************************************/
		/* Desenha Normal                                                       */
		/************************************************************************/
		glUseProgram(uiProgramId);
		glUniform3f(ptrApp->GetLightDirectionId(), ptrApp->GetLightDirection().x, ptrApp->GetLightDirection().y, ptrApp->GetLightDirection().z);

		/* DO THE RENDER */
		//DebugDraw();
		this->OnRender();
		

		/************************************************************************/
		/* Prepara para desenhar Billboard                                      */
		/************************************************************************/
		glUseProgram(this->uiBillboardProgramId);
		this->OnRenderBillboard();

		/************************************************************************/
		/* Prepara para desenhar Particles                                      */
		/************************************************************************/
		glUseProgram(this->uiParticleProgramId);
		// Same as the billboards tutorial
		glm::mat4 ViewMatrix = ptrController->getViewMatrix();
		glm::mat4 ViewProjectionMatrix = ptrController->getProjectionMatrix() * ViewMatrix;

		glUniform3f(this->uiParticleCameraRightWorldspaceId, ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
		glUniform3f(this->uiParticleCameraUpWorldspaceId, ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);

		glUniformMatrix4fv(ptrApp->GetParticleViewProjMatrixId(), 1, GL_FALSE, &ViewProjectionMatrix[0][0]);
		this->OnRenderParticle();

		// BLUR
		//if (i == 0)
		//	glAccum(GL_LOAD, 1.0 / n);
		//else
		//	glAccum(GL_ACCUM, 1.0 / n);

		//i++;

		//if (i >= n) {
		//	i = 0;
		//	glAccum(GL_RETURN, 1.0);
		//	//glAccum(GL_RETURN, 0.95);
		//	glfwSwapBuffers(ptrWindow);
		//}

		/* Por fim, troca os buffers */
		glfwSwapBuffers(ptrWindow);
		
		glfwPollEvents();

	} while (glfwGetKey(ptrWindow, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(ptrWindow) == 0);

	/* Clean stuff */
	glDeleteProgram(uiProgramId);
	glDeleteProgram(uiShadowProgramId);
	glDeleteFramebuffers(1, &FramebufferName);
	glDeleteTextures(1, &uiDepthTextureId);
	glDeleteVertexArrays(1, &VertexArrayID);

	glfwTerminate();
}

/************************************************************************/
/* File: Application.h                                                  */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once // Mesmo que #ifdef

/* Standard Includes */
#include <vector>
#include <string>
#include <functional>

/* Windows includes */
#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

/* GL Includes */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/* GLM Includes */
#include <glm/glm.hpp>

/* Util Includes */
#include "Entity.h"

using namespace std;

/**
\class Application
\brief Responsavel por controlar o programa, bem como guardar variáveis necessárias em todo o código
*/
class Application
{

public:

	struct p {
		glm::vec3 from, to;
	};

	std::vector<struct p> pontos;

	void DebugDraw();

private:
	string					strAppName;					//!< nome do titulo da janela da aplicacao
	string					strCurrentFPS;				//!< valor corrente (convertido em texto) do FPS disponivel para execucao da aplicacao

	int						iWindowWidth;				//!< largura da janela da aplicacao
	int						iWindowHeight;				//!< altura da janela da aplicacao
	
	unsigned int			uiFrames;					//!< contador de frames para o calculo do FPS
	unsigned int			uiFrameRate;				//!< quantidade de FPS atualizado a cada segundo	

	unsigned int			uiDepthTextureId;			//!< id da textura de profundidade para o shader
	unsigned int			uiTextureId;				//!< id da textura que vai ser enviada ao shader
	unsigned int			uiShadowMapId;				//!< id do mapa de sombras para o shader

	unsigned int			uiDepthMatrixId;			//!< id da matriz de profundidade para o shader
	unsigned int			uiMVPMatrixId;				//!< id da matriz de Model, View e Projection para o shader
	unsigned int			uiModelMatrixId;			//!< id da matriz de modelo para o shader. Usada para desenhar o objeto no mundo
	unsigned int			uiViewMatrixId;				//!< id da matriz de vista para o shader. Usada para realizar operacoes de camera
	unsigned int			uiDepthBiasId;				//!< id da matriz usada para melhorar a precisao de desenho de poligonos distantes
	unsigned int			uiLightDirectionId;			//!< id da matriz que armazena as coordenadas da luz

	unsigned int			uiAmbientMaterial;			//!< id do local onde o shader guarda informacoes de Ambient Lightning
	unsigned int			uiSpecularMaterial;			//!< id do local no shader que guarda informacoes de Specular Lightning

	unsigned int			uiProgramId;				//!< ID do programa de shaders
	unsigned int			uiShadowProgramId;			//!< ID do programa de shaders para sombra


	/* BILLBOARD */
	unsigned int			uiBillboardProgramId;			//!< ID do programa de shaders para billboard

	unsigned int			uiBillboardCameraRightId;		//!< id da matriz de camera a direita para billboard
	unsigned int			uiBillboardCameraUpId;			//!< id da matriz de camera para cima para billboard
	unsigned int			uiBillboardViewProjMatrixId;	//!< id da matriz view x projection para billboard
	unsigned int			uiBillboardPositionId;			//!< id da posicao do billboard
	unsigned int			uiBillboardSizeId;				//!< id do tamanho do billboard
	unsigned int			uiBillboardStatusId;			//!< id da de uma info extra do billboard
	unsigned int			uiBillboardTextureId;			//!< id da textura do  billboard

	/* PARTICLE */

	unsigned int			uiParticleProgramId;
	unsigned int			uiParticleCameraRightWorldspaceId;
	unsigned int			uiParticleCameraUpWorldspaceId;
	unsigned int			uiParticleViewProjMatrixId;
	unsigned int			uiParticleTextureId;

	/* UTILITY */


	double					dCounterTimer;				//!< contador de tempo para o calculo do FPS
	double					dTotalTime;					//!< contador de tempo desde o inicio do programa


	GLFWwindow*				ptrWindow;					//!< pointer para a janela principal criada pelo GLFW

	const glm::mat4			m4Unitaria = mat4(1);		//!< matriz 4x4 iniciada em 1 enviada aos objetos para eles aplicarem suas transformacoes ( rotacao, translacao, etc )
	glm::mat4				m4DepthProjection;			//!< matriz para projecao
	glm::mat4				m4DepthView;				//!< matriz para a visao da janela

	glm::vec3				v3LightDirection;			//!< vetor para a posicao da luz

	vector<class Entity*>	listOfEntities;				//!< lista de ponteiros para entidades que pertencem a cena sendo renderizada/animada
	vector<class ParticleSystem*>listOfParticleSys;		//!< lista com os sistemas de particulas
	vector<class Entity2D*>	listOfBillboards;			//!< lista de ponteiros para billboards que pertencem a cena sendo renderizada/animada
	vector<class Vehicle*>	listOfVehicles;				//!< lista de vehiculos para Steering Behaviour
	// Possible TODO: transformar em Entities

	typedef struct Function
	{
		function<void(double)>		fFuncToExecute;
		double						dTimeToExecute;
	} Function;

	vector<Function>		listOfFunctions;


public:
	/* TODO: Mudar para a classe Camera */
	glm::vec3				*ptrv3LookAtPos = NULL;		//!< pointer para a posicao que a camera deve olhar
	glm::vec3				*ptrv3CameraPos = NULL;		//!< posicao da camera no mundo

	class Entity			*ptraCameraTarget = NULL;	//!< pointer para o ator que será o foco da camera

	class Entity			*ptrcMainCamera = NULL;		//!< pointer para a camera principal da cena

	class Light				*ptrlMainLight = NULL;		//!< pointer para a luz principal da cena

	int						iParticleCount = 0;


private:

	/**
	\brief Efetua o calculo do FPS (Frames per Second) disponivel
	\param dElapsedTime tempo transcorrido entre duas chamadas consecutivas da funcao
	*/
	void CalculateFPS(double dElapsedTime);

	/**
	\brief Gera a janela visivel ao usuário e inicia algumas variaveis
	*/
	void StartWindow();

	/**
	\brief Adiciona uma nova entidade renderizavel a cena sendo manipulada
	\param ptrEnt ponteiro para a nova entidade a ser adicionada a cena
	*/
	void AddFunction(Function);


public:
	Application(unsigned int, unsigned int, string = "OAC 2017");
	~Application();

	/**
	\brief Inicia o aplicativo e carrega as configuracoes princpais
	*/
	void InitApplication();

	/**
	\brief Retorna o valor corrente da largura da janela da aplicacao
	\return unsigned int o valor da largura da janela
	*/
	inline GLFWwindow* GetWindow() { return this->ptrWindow; }

	/**
	\brief Retorna o valor corrente da largura da janela da aplicacao
	\return unsigned int o valor da largura da janela
	*/
	inline unsigned int GetWidth() { return this->iWindowWidth; }
	/**
	\brief Retorna o valor corrente da altura da janela da aplicacao
	\return unsigned int o valor da alura da janela
	*/
	inline unsigned int GetHeight() { return this->iWindowHeight; }

	/**
	\brief Retorna o valor corrente do titulo da aplicacao.<br>
	O titulo e o resultado do nome da aplicacao + o valor corrente para o FPS.

	\return string titulo da aplicacao
	*/
	inline string GetTitle() { return this->strAppName + " - [" + this->strCurrentFPS + "]"; }


	/************************************************************************/
	/* Shader Gets                                                          */
	/************************************************************************/

	/**
	\brief Retorna a matriz de projecao de profundidade
	\return Matriz 4x4 de float de projecao de profundidade
	*/
	inline glm::mat4 GetDepthProjectionMatrix() { return this->m4DepthProjection; };

	/**
	\brief Retorna a matriz de visualizacao de profundidade
	\return Matriz 4x4 de float de vizualizacao de profundidade
	*/
	inline glm::mat4 GetDepthViewMatrix() { return this->m4DepthView; };

	/**
	\brief Retorna o vetor da direcao da luz
	\return vetor com 3 coordenadas (x, y, z) da direcao da luz
	*/
	inline glm::vec3 GetLightDirection() { return this->v3LightDirection; };

	/**
	\brief Retorna o id da matriz de profundidade
	\return unsigned int do ID da matriz de profundidade
	*/
	inline unsigned int GetDepthMatrixId() { return this->uiDepthMatrixId; };

	/**
	\brief Retorna o id da matriz MVP ( Model View Projection )
	\return unsigned int do ID da matriz MVP
	*/
	inline unsigned int GetMVPMatrixId() { return this->uiMVPMatrixId; };

	/**
	\brief Retorna o id da matriz de profundidade
	\return unsigned int do ID da matriz de profundidade
	*/
	inline unsigned int GetModelMatrixID() { return this->uiModelMatrixId; };

	/**
	\brief Retorna o id da matriz de view
	\return unsigned int do ID da matriz de view
	*/
	inline unsigned int GetViewMatrixId() { return this->uiViewMatrixId; };

	/**
	\brief Retorna o id da matriz de bias para desenho
	\return unsigned int do ID da matriz de bias
	*/
	inline unsigned int GetDepthBiasID() { return this->uiDepthBiasId; };

	/**
	\brief Retorna o id da matriz de bias para desenho
	\return unsigned int do ID da matriz de bias
	*/
	inline unsigned int GetLightDirectionId() { return this->uiLightDirectionId; };
	
	/**
	\brief Retorna o id da matriz de btextura
	\return unsigned int do ID da textura
	*/
	inline unsigned int GetTextureId() { return this->uiTextureId; };

	/**
	\brief Retorna o id da matriz de textura de profundidade
	\return unsigned int do ID da matriz de textura de profundidade
	*/
	inline unsigned int GetDepthTextureId() { return this->uiDepthTextureId; };

	/**
	\brief Retorna o id da matriz de textura de sombra
	\return unsigned int do ID da matriz de textura de sombra
	*/
	inline unsigned int GetShadowMapId() { return this->uiShadowMapId; };

	/**
	\brief Retorna o id do vetor de Specular Lightning
	\return unsigned int do ID do vetor de Specular Lightning
	*/
	inline unsigned int GetSpecularLightingId() { return this->uiSpecularMaterial; };

	/**
	\brief Retorna o id do vetor de Ambient Lightning
	\return unsigned int do ID do vetor de Ambient Lightning
	*/
	inline unsigned int GetAmbientLightingId() { return this->uiAmbientMaterial; };

	/************************************************************************/
	/* Gets do Billboard		                                            */
	/************************************************************************/

	/**
	\brief Retorna o id do vetor de Ambient Lightning
	\return unsigned int do ID do vetor de Ambient Lightning
	*/
	inline unsigned int GetBillboardCameraRightId() { return this->uiBillboardCameraRightId; };

	/**
	\brief Retorna o id do vetor de Ambient Lightning
	\return unsigned int do ID do vetor de Ambient Lightning
	*/
	inline unsigned int GetBillboardCameraUpId() { return this->uiBillboardCameraUpId; };

	/**
	\brief Retorna o id do vetor de Ambient Lightning
	\return unsigned int do ID do vetor de Ambient Lightning
	*/
	inline unsigned int GetBillboardViewProjMatrixId() { return this->uiBillboardViewProjMatrixId; };

	/**
	\brief Retorna o id do vetor de Ambient Lightning
	\return unsigned int do ID do vetor de Ambient Lightning
	*/
	inline unsigned int GetBillboardPositionId() { return this->uiBillboardPositionId; };

	/**
	\brief Retorna o id do vetor de Ambient Lightning
	\return unsigned int do ID do vetor de Ambient Lightning
	*/
	inline unsigned int GetBillboardSizeId() { return this->uiBillboardSizeId; };

	/**
	\brief Retorna o id do vetor de Ambient Lightning
	\return unsigned int do ID do vetor de Ambient Lightning
	*/
	inline unsigned int GetBillboardStatusId() { return this->uiBillboardStatusId; };

	/**
	\brief Retorna o id do vetor de Ambient Lightning
	\return unsigned int do ID do vetor de Ambient Lightning
	*/
	inline unsigned int GetBillboardTextureId() { return this->uiBillboardTextureId; };

	/**
	\brief Adiciona uma nova bilboard renderizavel a cena sendo manipulada
	\param ptrEnt ponteiro para a nova bilboard a ser adicionada a cena
	*/
	void AddBillboard(Entity2D* ptrBilboard);

	/**
	\brief Metodo responsavel por desenhar cada frame da aplicacao
	*/
	void OnRenderBillboard();

	/**
	\brief Metodo responsavel por desenhar as sombras na textura de sombra
	*/
	void OnPreRenderBillboard();

	/************************************************************************/
	/* Gets de Particle  		                                            */
	/************************************************************************/

	inline unsigned int GetParticleProgramId() { return this->uiParticleProgramId; };
	inline unsigned int GetParticleTextureId() { return this->uiParticleTextureId; };
	inline unsigned int GetParticleCameraRightWorldspaceId() { return this->uiParticleCameraRightWorldspaceId; };
	inline unsigned int GetParticleCameraUpWorldspaceId() { return this->uiParticleCameraUpWorldspaceId; };
	inline unsigned int GetParticleViewProjMatrixId() { return this->uiParticleViewProjMatrixId; };

	void AddParticleSystem(ParticleSystem* ptrParticleSystem);

	/**
	\brief Metodo responsavel por desenhar cada frame da aplicacao
	*/
	void OnRenderParticle();


	/************************************************************************/
	/* Funcoes do App			                                            */
	/************************************************************************/


	/**
	\brief Calcula o tempo desde o inicio da aplicacao
	\return double a quantidade de tempo desde o inicio da aplicacao
	*/
	inline double GetApplicationTime() { return this->dTotalTime; };

	/**
	\brief Executa o loop principal da aplicacao IDS
	\param dElapsedTime tempo transcorrido (em milisegundos) entre duas chamadas consecutivas da funcao
	\return int flag que indica sucesso ou falha na execucao
	*/
	int Execute(double);

	/**
	\brief Metodo responsavel por desenhar cada frame da aplicacao
	*/
	void OnRender();

	/**
	\brief Metodo responsavel por desenhar as sombras na textura de sombra
	*/
	void OnPreRender();

	/**
	\brief Adiciona uma nova entidade renderizavel a cena sendo manipulada
	\param ptrEnt ponteiro para a nova entidade a ser adicionada a cena
	*/
	void AddEntity(Entity*);


	/**
	\brief Altera uma dada entidade pertencente a cena sendo manipulada
	\param ptrEnt ponteiro para a nova entidade a ser adicionada a cena
	\param uiIndex posicao da entidade na lista de entidades da cena
	\return flag que indica se houve sucesso na operacao
	*/
	bool SetEntity(Entity*, unsigned int);

	/**
	\brief Retorna uma dada entidade da cena sendo manipulada
	\param uiIndex posicao da entidade na lista de entidades da cena a ser retornada
	\return ponteiro para a dade entidade ou NULL caso indice invalido
	*/
	Entity* GetEntity(unsigned int);
	
	void AddTimerFunction(function<void(double)> fFuncToExecute, double dTimeToExecute);

	int getEntityCount();

	vector<Entity*> getEntities() { return this->listOfEntities; };

	void AddVehicle(Vehicle* veh) { this->listOfVehicles.push_back(veh); };
	vector<Vehicle*> getVehicles() { return this->listOfVehicles; };
};


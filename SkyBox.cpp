#include "stdafx.h"
#include "SkyBox.h"

#include "Constants.h"
#include "Shader.h"
#include "TextureLoader.h"
#include "Controller.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

SkyBox::SkyBox()
{
}


SkyBox::~SkyBox()
{
}

void SkyBox::Initialize()
{

	skyboxProgram = ptrShader->LoadShaders("shaders/skybox.vertexshader", "shaders/skybox.fragmentshader");

	vector<const GLchar*> faces;
	faces.push_back("textures/skybox/ocean/right.jpg");
	faces.push_back("textures/skybox/ocean/left.jpg");
	faces.push_back("textures/skybox/ocean/top.jpg");
	faces.push_back("textures/skybox/ocean/bottom.jpg");
	faces.push_back("textures/skybox/ocean/back.jpg");
	faces.push_back("textures/skybox/ocean/front.jpg");
	cubemapTexture = ptrTextureLoader->loadCubemap(faces);

	float skyboxVertices[] = {
		// Positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f
	};
	
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);

}

void SkyBox::OnRender()
{
	glUseProgram(skyboxProgram);
	glm::mat4 view = glm::mat4(glm::mat3(ptrController->getViewMatrix()));	// Remove any translation component of the view matrix
	glm::mat4 projection = ptrController->getProjectionMatrix();
	glUniformMatrix4fv(glGetUniformLocation(skyboxProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(skyboxProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	// skybox cube
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(skyboxProgram, "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}


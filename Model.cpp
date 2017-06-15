/************************************************************************/
/* File: MOdelo.cpp                                                     */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

/* Basic Includes */
#include "stdafx.h"
#include "Model.h"

/* OpenGL Includes*/
#include <Windows.h>
#include <GL/glew.h>
#include <gl\gl.h>

/* Utility Includes */
#include "OBJLoader.h"
#include "TextureLoader.h"
#include "Constants.h"
#include "Controller.h"
#include "Entity.h"

/* Standard Includes */
#include <vector>

/* GLM Includes */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/norm.hpp>

Model::Model(const char* objfile, const char* texture, vec3 ambient, vec3 specular)
{
	ptrMaterial = new Material(texture, ambient, specular, 1.0f);

	std::vector<glm::vec3> indexed_vertices;
	std::vector<glm::vec2> indexed_uvs;
	std::vector<glm::vec3> indexed_normals;

	ObjectStruct objLoaded = ptrObjLoader->LoadAssImp(objfile);

	v3Vertices = objLoaded.v3Vertices;
	v3UVs = objLoaded.v3UVs;
	v3Normals = objLoaded.v3Normals;
	vuiIndices = objLoaded.vuiIndices;

	/* GET OBJECT'S DIMENSION */
	this->vMaxValue = objLoaded.vMaxValue;
	this->vMinValue = objLoaded.vMinValue;
	this->fRadius = glm::distance(vMaxValue, vMinValue) / 2.0f;
	/* END DIMENSIONING */


	glGenBuffers(1, &this->uiVertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, this->uiVertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, v3Vertices.size() * sizeof(glm::vec3), &v3Vertices[0], GL_STATIC_DRAW);

	if (v3UVs.size() > 0) {
		glGenBuffers(1, &this->uiUVBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, this->uiUVBufferId);
		glBufferData(GL_ARRAY_BUFFER, v3UVs.size() * sizeof(glm::vec2), &v3UVs[0], GL_STATIC_DRAW);
	}


	glGenBuffers(1, &this->uiNormalBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, this->uiNormalBufferId);
	glBufferData(GL_ARRAY_BUFFER, v3Normals.size() * sizeof(glm::vec3), &v3Normals[0], GL_STATIC_DRAW);

	// Generate a buffer for the indices as well
	glGenBuffers(1, &this->uiElementBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->uiElementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vuiIndices.size() * sizeof(unsigned short), &vuiIndices[0], GL_STATIC_DRAW);
}


Model::~Model()
{
	delete this->ptrMaterial;
	glDeleteBuffers(1, &this->uiVertexBufferId);
	glDeleteBuffers(1, &this->uiUVBufferId);
	glDeleteBuffers(1, &this->uiNormalBufferId);
	glDeleteBuffers(1, &this->uiElementBufferId);
}

/**
\brief Rotina de renderizacao de sombra do objeto em OPENGL.
*/
void Model::OnPreRender(glm::mat4 _ModelMatrix)
{
	m4ModelMatrix = _ModelMatrix;


	m4ModelMatrix = glm::translate(m4ModelMatrix, this->vTranslate) * glm::toMat4(qOrientation);

	m4ModelMatrix = glm::scale(m4ModelMatrix, this->vScale);


	if (this->bIsShearable) {
		m4ModelMatrix = glm::shearX3D(m4ModelMatrix, this->fShearAmountA, this->fShearAmountB);
	}

	m4DepthMVP = ptrApp->GetDepthProjectionMatrix() * ptrApp->GetDepthViewMatrix() * m4ModelMatrix;

	if (this->bIsWireframe) {
		return;
	}

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(ptrApp->GetDepthMatrixId(), 1, GL_FALSE, &m4DepthMVP[0][0]);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->uiVertexBufferId);
	glVertexAttribPointer(
		0,  // The attribute we want to configure
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->uiElementBufferId);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		vuiIndices.size(),    // count
		GL_UNSIGNED_SHORT, // type
		(void*)0           // element array buffer offset
	);

	glDisableVertexAttribArray(0);
}

/**
\brief Rotina de renderizacao do objeto em OPENGL.
*/
void Model::OnRender(glm::mat4 _ModelMatrix)
{
	if (this->bIsWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	// Compute the MVP matrix from keyboard and mouse input
	glm::mat4 ProjectionMatrix = ptrController->getProjectionMatrix();
	glm::mat4 ViewMatrix = ptrController->getViewMatrix();
	//ViewMatrix = glm::lookAt(glm::vec3(14,6,4), glm::vec3(0,1,0), glm::vec3(0,1,0));

	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * this->m4ModelMatrix;

	static glm::mat4 biasMatrix(
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	);

	glm::mat4 depthBiasMVP = biasMatrix*m4DepthMVP;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(ptrApp->GetMVPMatrixId(), 1, GL_FALSE, &MVP[0][0]);
	glUniformMatrix4fv(ptrApp->GetModelMatrixID(), 1, GL_FALSE, &this->m4ModelMatrix[0][0]);
	glUniformMatrix4fv(ptrApp->GetViewMatrixId(), 1, GL_FALSE, &ViewMatrix[0][0]);
	glUniformMatrix4fv(ptrApp->GetDepthBiasID(), 1, GL_FALSE, &depthBiasMVP[0][0]);	

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->ptrMaterial->GetTextureId());

	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(ptrApp->GetTextureId(), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ptrApp->GetDepthTextureId());
	glUniform1i(ptrApp->GetShadowMapId(), 1);

	/* SEND MATERIAL DATA */

	glUniform3f(ptrApp->GetSpecularLightingId(), this->ptrMaterial->GetSpecularColor().x, this->ptrMaterial->GetSpecularColor().y, this->ptrMaterial->GetSpecularColor().z);
	glUniform3f(ptrApp->GetAmbientLightingId(), this->ptrMaterial->GetAmbientColor().x, this->ptrMaterial->GetAmbientColor().y, this->ptrMaterial->GetAmbientColor().z);

	/* END SENDIND MATERIAL DATA */

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, uiVertexBufferId);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	if (v3UVs.size() > 0) {
		// 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uiUVBufferId);
		glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
	}

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, uiNormalBufferId);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiElementBufferId);

	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		vuiIndices.size(),    // count
		GL_UNSIGNED_SHORT, // type
		(void*)0           // element array buffer offset
	);

	if (this->bIsWireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	//for (std::vector<Entity*>::iterator pointer = this->listOfEntities.begin(); pointer != this->listOfEntities.end(); pointer++)
	//	(*pointer)->OnRender(ModelMatrix, MatrixID, ModelMatrixID, ViewMatrixID, DepthBiasID, lightInvDirID, lightInvDir,
	//		TextureID, depthTexture, ShadowMapID);
}

/**
\brief Carrega as dimensoes do modelo
*/
void Model::LoadDimensions()
{
	vMaxValue.x *= this->vScale.x;
	vMaxValue.y *= this->vScale.y;
	vMaxValue.z *= this->vScale.z;

	vMinValue.x *= this->vScale.x;
	vMinValue.y *= this->vScale.y;
	vMinValue.z *= this->vScale.z;

	vCenter = (vMaxValue + vMinValue) / 2.0f;

	vDimensionSize = vMaxValue - vMinValue;

	this->fRadius *= max(max(this->vScale.x, this->vScale.y), this->vScale.z);

	bHasLoadedDimensions = true;
}

/**
\brief Atualiza os parametros da primitiva para o proximo frame da animacao
\param dDeltaTime tempo transcorrido entre duas atualizacoes sucessivas (em milisegundos)
*/
void Model::OnLoop(double dDeltaTime)
{
	Entity::OnLoop(dDeltaTime);
}

/************************************************************************/
/* File: Application.h                                                  */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

/* Basic Includes */
#include "stdafx.h"
#include "BillBoard.h"

/* OpenGL Includes */
#include <Windows.h>
#include <GL/glew.h>
#include <gl/gl.h>

/* Utility Includes */
#include "Constants.h"
#include "Application.h"
#include "Controller.h"
#include "TextureLoader.h"

bool BillBoard::bHasAnyLoaded = false;

unsigned int BillBoard::uiVertexBufferId;

BillBoard::BillBoard(const char* texture)
{
	this->uiTextureId = ptrTextureLoader->LoadTexture(texture);
	glBindTexture(GL_TEXTURE_2D, uiTextureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	// The VBO containing the 4 vertices of the particles.
	if (!bHasAnyLoaded) {
		static const GLfloat g_vertex_buffer_data[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f,
			0.5f,  0.5f, 0.0f,
		};
		glGenBuffers(1, &uiVertexBufferId);
		glBindBuffer(GL_ARRAY_BUFFER, uiVertexBufferId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
		bHasAnyLoaded = true;
	}

	this->fDeltaShear = (rand() % 180) / 10.0f;
	this->bIsShearable = false;
	this->SetSize(vec2(1,1));
	this->setTranslate(vec3(0,0,0));
}

BillBoard::~BillBoard()
{

}

void BillBoard::OnPreRender(glm::mat4)
{

}

void BillBoard::OnRender(glm::mat4 ModelMatrix)
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->uiTextureId);
	glUniform1i(ptrApp->GetBillboardTextureId(), 0);

	glm::mat4 ViewMatrix = ptrController->getViewMatrix();
	glm::vec3 CameraPosition(glm::inverse(ViewMatrix)[3]);
	glm::mat4 ViewProjectionMatrix = ptrController->getProjectionMatrix() * ViewMatrix;

	glUniform3f(ptrApp->GetBillboardCameraRightId(), ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]);
	glUniform3f(ptrApp->GetBillboardCameraUpId(), ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]);

	glUniform3f(ptrApp->GetBillboardPositionId(), this->v3Position.x, this->v3Position.y, this->v3Position.z);
	glUniform2f(ptrApp->GetBillboardSizeId(), this->v2Size.x, this->v2Size.y );

	float LifeLevel = 0.0f;
	if (this->bIsShearable) LifeLevel = (sin(ptrApp->GetApplicationTime() + fDeltaShear) - 0.2f) * 0.2;

	glUniform1f(ptrApp->GetBillboardStatusId(), LifeLevel);

	glUniformMatrix4fv(ptrApp->GetBillboardViewProjMatrixId(), 1, GL_FALSE, &ViewProjectionMatrix[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, uiVertexBufferId);
	glVertexAttribPointer(
		0,      
		3,      
		GL_FLOAT,  
		GL_FALSE, 
		0, 
		(void*)0 
	);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(0);
}

void BillBoard::setTranslate(glm::vec3 translate)
{
	this->v3Position = translate;
}

void BillBoard::SetSize(glm::vec2 size)
{
	this->v2Size = size;
}

void BillBoard::OnLoop(double dDeltaTime)
{

}

void BillBoard::SetShearable(bool bShear)
{
	this->bIsShearable = bShear;
}

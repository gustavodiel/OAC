#include "stdafx.h"
#include "Cloth.h"

#include "Constants.h"
#include "Application.h"
#include "Controller.h"
#include "Camera.h"
#include "TextureLoader.h"

#include "Model.h"
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include "Utilities.hpp"

#define CONSTRAINT_ITERATIONS 5 // how many iterations of constraint satisfaction each frame (more is rigid, less is soft


Cloth::Cloth(float width, float height, int num_particles_width, int num_particles_height) :
	num_particles_width(num_particles_width),
	num_particles_height(num_particles_height)
{

	this->particles.resize(num_particles_width * num_particles_height);

	ptrMaterial = new Material("textures/branco.jpg", vec3(0,1,1), vec3(0.01, 0.01, 0.01), 1.0f);

	for (int x = 0; x<num_particles_width; x++)
	{
		for (int y = 0; y<num_particles_height; y++)
		{
			vec3 pos = vec3(width * (x / (float)num_particles_width),
				height * (y / (float)num_particles_height),
				0);
			particles[y*num_particles_width + x] = Vertice3D(pos); // insert particle in column x at y'th row
		}
	}

	// Connecting immediate neighbor particles with constraints (distance 1 and sqrt(2) in the grid)
	for (int x = 0; x<num_particles_width; x++)
	{
		for (int y = 0; y<num_particles_height; y++)
		{
			if (x<num_particles_width - 1) MakeConstraint(GetVertice(x, y), GetVertice(x + 1, y));
			if (y<num_particles_height - 1) MakeConstraint(GetVertice(x, y), GetVertice(x, y + 1));
			if (x<num_particles_width - 1 && y<num_particles_height - 1) MakeConstraint(GetVertice(x, y), GetVertice(x + 1, y + 1));
			if (x<num_particles_width - 1 && y<num_particles_height - 1) MakeConstraint(GetVertice(x + 1, y), GetVertice(x, y + 1));
		}
	}


	// Connecting secondary neighbors with constraints (distance 2 and sqrt(4) in the grid)
	for (int x = 0; x<num_particles_width; x++)
	{
		for (int y = 0; y<num_particles_height; y++)
		{
			if (x<num_particles_width - 2) MakeConstraint(GetVertice(x, y), GetVertice(x + 2, y));
			if (y<num_particles_height - 2) MakeConstraint(GetVertice(x, y), GetVertice(x, y + 2));
			if (x<num_particles_width - 2 && y<num_particles_height - 2) MakeConstraint(GetVertice(x, y), GetVertice(x + 2, y + 2));
			if (x<num_particles_width - 2 && y<num_particles_height - 2) MakeConstraint(GetVertice(x + 2, y), GetVertice(x, y + 2));
		}
	}

	this->GetVertice(0, num_particles_height - 1)->OffsetPosition(vec3(-0.2, 0, 0));
	this->GetVertice(0, num_particles_height - 1)->MakeStatic();
	this->GetVertice(num_particles_width - 1, num_particles_height - 1)->OffsetPosition(vec3(0.2, 0, 0));
	this->GetVertice(num_particles_width - 1, num_particles_height - 1)->MakeStatic();

	this->vWind = vec3(0, 0, 0);
	this->vGravity = vec3(0, 0, 0);


	uiPositionAttributeLocation = 0;	
	uiNormalAttributeLocation = 1;
	uiUVAttributeLocation = 2;


	std::vector<int> vuiIndices;


	for (int j = 0; j < num_particles_height - 1; j++) {
		int index;
		if (j > 0) {
			vuiIndices.push_back(j * num_particles_width); // make degenerate
		}
		for (int i = 0; i <= num_particles_width - 1; i++) {
			index = j * num_particles_width + i;
			vuiIndices.push_back(index);
			vuiIndices.push_back(index + num_particles_width);
		}
		if (j + 1 < num_particles_height - 1) {
			vuiIndices.push_back(index + num_particles_width); // make degenerate
		}
	}
	iElementSize = vuiIndices.size();

	glGenBuffers(1, &uiElementArrayBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiElementArrayBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, iElementSize * sizeof(int), &(vuiIndices[0]), GL_STATIC_DRAW);

	glGenBuffers(1, &this->uiVertexBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, this->uiVertexBufferId);

	glGenBuffers(1, &this->uiUVBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, this->uiUVBufferId);

	glGenBuffers(1, &this->uiNormalBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, this->uiNormalBufferId);

	uiTextureId = ptrTextureLoader->LoadTexture("textures/tapete.jpg");//generateCustomTexture(num_particles_width);
}

void Cloth::OnPreRender(mat4 _ModelMatrix) {
	// TODO OnPreREnder
	// reset normals (which where written to last frame)
	glDisable(GL_CULL_FACE);
	std::vector<Vertice3D>::iterator particle;
	for (particle = particles.begin(); particle != particles.end(); particle++)
	{
		(*particle).ResetNormal();
	}

	m4ModelMatrix = glm::translate(_ModelMatrix, this->vTranslate);

	m4ModelMatrix = glm::rotate(m4ModelMatrix, glm::radians(this->vRotate.z), glm::vec3(0.0f, 0.0f, 1.0f));
	m4ModelMatrix = glm::rotate(m4ModelMatrix, glm::radians(this->vRotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
	m4ModelMatrix = glm::rotate(m4ModelMatrix, glm::radians(this->vRotate.x), glm::vec3(1.0f, 0.0f, 0.0f));

	m4ModelMatrix = glm::scale(m4ModelMatrix, this->vScale);

	//create smooth per particle normals by adding up all the (hard) triangle normals that each particle is part of
	for (int x = 0; x < num_particles_width - 1; x++)
	{
		for (int y = 0; y < num_particles_height - 1; y++)
		{
			vec3 normal = GerarNormalTriangulo(GetVertice(x + 1, y), GetVertice(x, y), GetVertice(x, y + 1));
			GetVertice(x + 1, y)->AddToNormal(normal);
			GetVertice(x, y)->AddToNormal(normal);
			GetVertice(x, y + 1)->AddToNormal(normal);

			normal = GerarNormalTriangulo(GetVertice(x + 1, y + 1), GetVertice(x + 1, y), GetVertice(x, y + 1));
			GetVertice(x + 1, y + 1)->AddToNormal(normal);
			GetVertice(x + 1, y)->AddToNormal(normal);
			GetVertice(x, y + 1)->AddToNormal(normal);
		}
	}

	std::vector<Vertex> vertexData;

	for (int y = 0; y < num_particles_height; y++)
	{
		for (int x = 0; x < num_particles_width; x++)
		{
			vec2 uv(x / (num_particles_width - 1.0f), y / (num_particles_height - 1.0f));

			CreateTriangle(GetVertice(x, y), uv, vertexData);
		}
	}

	m4DepthMVP = ptrApp->GetDepthProjectionMatrix() * ptrApp->GetDepthViewMatrix() * m4ModelMatrix;

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	glUniformMatrix4fv(ptrApp->GetDepthMatrixId(), 1, GL_FALSE, &m4DepthMVP[0][0]);

	vector<glm::vec3> positions;
	for (unsigned int i = 0; i < vertexData.size(); ++i) {
		positions.push_back(vertexData[i].position);
	}

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(uiPositionAttributeLocation);
	glBindBuffer(GL_ARRAY_BUFFER, uiVertexBufferId);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(vec3), &positions[0], GL_DYNAMIC_DRAW); //GL_STREAM_DRAW
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiElementArrayBufferId);

	glDrawElements(GL_TRIANGLE_STRIP, iElementSize, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glEnable(GL_CULL_FACE);

}

void Cloth::OnRender(mat4 m4ModelMatrix) {
	// TODO OnPreREnder
	// reset normals (which where written to last frame)
	glDisable(GL_CULL_FACE);



	std::vector<Vertex> vertexData;

	for (int y = 0; y < num_particles_height; y++)
	{
		for (int x = 0; x < num_particles_width; x++)
		{
			vec2 uv(x / (num_particles_width - 1.0f), y / (num_particles_height - 1.0f));

			CreateTriangle(GetVertice(x, y), uv, vertexData);
		}
	}
	glm::mat4 ProjectionMatrix = ptrController->getProjectionMatrix();
	glm::mat4 ViewMatrix = ptrController->getViewMatrix();
	//ViewMatrix = glm::lookAt(glm::vec3(14,6,4), glm::vec3(0,1,0), glm::vec3(0,1,0));

	glm::mat4 MVP = ProjectionMatrix * ViewMatrix * this->m4ModelMatrix;

	glm::mat4 biasMatrix(
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
	glUniform3f(ptrApp->GetLightDirectionId(), ptrApp->GetLightDirection().x, ptrApp->GetLightDirection().y, ptrApp->GetLightDirection().z);

	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, uiTextureId);

	// Set our "myTextureSampler" sampler to user Texture Unit 0
	glUniform1i(ptrApp->GetTextureId(), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, ptrApp->GetDepthTextureId());
	glUniform1i(ptrApp->GetShadowMapId(), 1);

	/* SEND MATERIAL DATA */

	glUniform3f(ptrApp->GetSpecularLightingId(), this->ptrMaterial->GetSpecularColor().x, this->ptrMaterial->GetSpecularColor().y, this->ptrMaterial->GetSpecularColor().z);
	glUniform3f(ptrApp->GetAmbientLightingId(), this->ptrMaterial->GetAmbientColor().x, this->ptrMaterial->GetAmbientColor().y, this->ptrMaterial->GetAmbientColor().z);

	/* END SENDIND MATERIAL DATA */
	vector<glm::vec2> v3UVs;
	vector<glm::vec3> v3Normals;
	if (!bLoaded) {		
		for (int i = 0; i < vertexData.size(); ++i) {
			v3UVs.push_back(vertexData[i].uv);
			v3Normals.push_back(vertexData[i].normal);
		}
	}

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(uiPositionAttributeLocation);
	glBindBuffer(GL_ARRAY_BUFFER, uiVertexBufferId);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

		// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(uiUVAttributeLocation);
	glBindBuffer(GL_ARRAY_BUFFER, uiUVBufferId);
	if (!bLoaded)
		glBufferData(GL_ARRAY_BUFFER, v3UVs.size() * sizeof(vec2), &v3UVs[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(
			1,                                // attribute
			2,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
	);
	

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(uiNormalAttributeLocation);
	glBindBuffer(GL_ARRAY_BUFFER, uiNormalBufferId);
	if (!bLoaded)
		glBufferData(GL_ARRAY_BUFFER, v3Normals.size() * sizeof(vec3), &v3Normals[0], GL_DYNAMIC_DRAW);
	bLoaded = true;
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiElementArrayBufferId);

	glDrawElements(GL_TRIANGLE_STRIP, iElementSize, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glEnable(GL_CULL_FACE);

}

void Cloth::OnLoop(double dDeltaTime)
{
	this->WindForce(this->vWind);
	for (vector<Utilities::TimeForce>::iterator itSF = vTimedWind.begin(); itSF < vTimedWind.end();) {
		if ((*itSF).time < ptrApp->GetApplicationTime()) {
			this->WindForce((*itSF).forca);
			if ((*itSF).time + 0.5f < ptrApp->GetApplicationTime()) {
				vTimedWind.erase(itSF);
				continue;
			}
		}
		itSF++;
	}

	this->AddForce(this->vGravity);
	for (vector<Utilities::TimeForce>::iterator itSF = vTimedForces.begin(); itSF < vTimedForces.end();) {
		if ((*itSF).time < ptrApp->GetApplicationTime()) {
			this->AddForce((*itSF).forca);
			vTimedForces.erase(itSF);
		}
		else {
			itSF++;
		}
	}

	if (ptrApp->ptrcMainCamera) {
		this->ProcessBallCollision(ptrApp->ptrcMainCamera->getTranslate() - vec3(0,0.5, -0.5), 0.5); // resolve collision with the ball
	}

	int constraintCount = static_cast<int>(constraints.size());
	for (int i = 0; i < CONSTRAINT_ITERATIONS; i++) // iterate over all constraints several times
	{
//#pragma omp parallel for
		for (int i = 0; i < constraintCount; ++i)
		{
			constraints[i].LimitarJuncao(dDeltaTime); // satisfy constraint.
		}
	}

	int particleCount = static_cast<int>(particles.size());

//#pragma omp parallel for
	for (int i = 0; i < particleCount; i++)
	{
		particles[i].OnLoop(dDeltaTime);
	}



}

void Cloth::AddForce(const vec3 direction)
{
	std::vector<Vertice3D>::iterator particle;
	for (particle = particles.begin(); particle != particles.end(); particle++)
	{
		(*particle).AddForce(direction); // add the forces to each particle
	}

}

void Cloth::AddForce(const vec3 direction, double time)
{
	Utilities::TimeForce fForca;
	fForca.forca = direction;
	fForca.time = time;
	this->vTimedForces.push_back(fForca);
}

/* used to add wind forces to all particles, is added for each triangle since the final force is proportional to the triangle area as seen from the wind direction*/
void Cloth::WindForce(const vec3 direction)
{
	for (int x = 0; x<num_particles_width - 1; x++)
	{
		for (int y = 0; y<num_particles_height - 1; y++)
		{
			AddWindToTriangle(GetVertice(x + 1, y), GetVertice(x, y), GetVertice(x, y + 1), direction);
			AddWindToTriangle(GetVertice(x + 1, y + 1), GetVertice(x + 1, y), GetVertice(x, y + 1), direction);
		}
	}
}

void Cloth::WindForce(const vec3 direction, double time)
{
	Utilities::TimeForce fForca;
	fForca.forca = direction;
	fForca.time = time;
	this->vTimedWind.push_back(fForca);
}

void Cloth::MakeConstraint(Vertice3D* p1, Vertice3D *p2) {
	constraints.push_back(Juncao(p1, p2));
}

vec3 Cloth::GerarNormalTriangulo(Vertice3D *p1, Vertice3D *p2, Vertice3D *p3) {
	vec3 pos1 = p1->GetPosition();
	return cross(p2->GetPosition() - pos1, p3->GetPosition() - pos1);
}

void Cloth::AddWindToTriangle(Vertice3D *p1, Vertice3D *p2, Vertice3D *p3, const vec3 direction) {
	vec3 normal = GerarNormalTriangulo(p1, p2, p3);
	vec3 d = normalize(normal);
	vec3 force = normal*(dot(d, direction));
	p1->AddForce(force);
	p2->AddForce(force);
	p3->AddForce(force);
}

void Cloth::ProcessBallCollision(const glm::vec3 center, const float radius)
{
	double media = 0;
	int parCount = particles.size();
	for (int i = 0; i < parCount; i++)
	{
		Vertice3D* particle = &particles[i];
		glm::vec3 v = particle->GetPosition() - center;
		float l = glm::length(v);
		media += l;
		if (l < radius) // if the particle is inside the ball
		{
			vec3 pos = glm::normalize(v)*(radius - l);
			particle->OffsetPosition(pos); // project the particle to the surface of the ball
		}
	}
}

void Cloth::CreateTriangle(Vertice3D *p1, const vec2 uv, std::vector<Vertex> &vertexData) {
	Vertex v1 = { p1->GetPosition(), uv, p1->GetNormal() };
	vertexData.push_back(v1);
}

Cloth::~Cloth()
{
}

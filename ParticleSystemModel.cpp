#include "stdafx.h"
#include "ParticleSystemModel.h"

#include <vector>
#include <algorithm>

#include <omp.h>

#include "Constants.h"
#include "Application.h"
#include "TextureLoader.h"
#include "Controller.h"
#include "Emitter.h"
#include "Utilities.hpp"

#include "OBJLoader.h"

ParticleSystemModel::ParticleSystemModel(const char* tex, int iMaxParticles, glm::vec3 vStartingPos, glm::vec3 vStartingDir) :
	cTextureName(tex),
	iMaxParticles(iMaxParticles)
{
	this->iLastUsedParticle = 0;

	this->ptrEmitter = new Emitter();
	ptrEmitter->setTranslate(vStartingDir);
	ptrEmitter->setRotate(vStartingDir);

	this->ptrfParticlePositionSizeData = new GLfloat[this->iMaxParticles * 4];
	this->ptrfParticleColorData = new GLubyte[this->iMaxParticles * 4];

	this->listOfParticles = (Particle*)malloc(sizeof(Particle) * iMaxParticles);

	for (int i = 0; i < this->iMaxParticles; i++) {
		this->listOfParticles[i].fLife = -1.0f;
		this->listOfParticles[i].fCameraDist = -1.0f;
	}


	// ******************************************************************************
	//					Create basic loop/birth/death particle functions
	// ******************************************************************************
	this->fnOnParticleBirth = [](double dDeltaTime, Particle *p, ParticleSystemModel* ps) {
		p->fLife = 2.0f;
		p->vPosition = ps->ptrEmitter->getTranslate();

		float spread = 1.5f;

		glm::vec3 randomdir = glm::vec3(
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f,
			(rand() % 2000 - 1000.0f) / 1000.0f
		);
		p->vSpeed = ps->ptrEmitter->getRotate() + randomdir*spread;

		p->cR = 255;
		p->cG = 255;
		p->cB = 255;
		p->cA = 255;

		p->fSize = (rand() % 1000) / 2000.0f + 0.1f;
	};

	this->fnOnParticleLoop = [](double dDeltaTime, Particle *p, ParticleSystemModel* ps) {
		p->vSpeed += glm::vec3(0.0f, -9.81f, 0.0f) * (float)dDeltaTime * 0.5f;
		p->vPosition += p->vSpeed * (float)dDeltaTime;
		//p->fSize *= 1 + dDeltaTime;
		p->cA = max(0, p->cA - 50 * dDeltaTime);
	};

	this->fnOnParticleDeath = [](double dDeltaTime, Particle *p, ParticleSystemModel* ps) {
		p->fCameraDist = -1.0f;
	};
	// ******************************************************************************
	//					End Custom functions
	// ******************************************************************************

	uiTextureId = ptrTextureLoader->LoadTexture("textures/branco.png");


	ObjectStruct objLoaded = ptrObjLoader->LoadAssImp("objs/peaoRigid.obj");

	this->sizeModel = objLoaded.v3Vertices.size() * sizeof(glm::vec3);

	glGenBuffers(1, &this->uiVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->uiVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, objLoaded.v3Vertices.size() * sizeof(glm::vec3), &objLoaded.v3Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &this->uiUVBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, this->uiUVBufferId);
	glBufferData(GL_ARRAY_BUFFER, objLoaded.v3UVs.size() * sizeof(glm::vec2), &objLoaded.v3UVs[0], GL_STATIC_DRAW);
	

	glGenBuffers(1, &this->uiPositionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->uiPositionBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->iMaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);

	glGenBuffers(1, &this->uiColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, this->uiColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->iMaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW);
}


ParticleSystemModel::~ParticleSystemModel()
{

}

int ParticleSystemModel::FindUnusedParticle()
{
	for (int i = this->iLastUsedParticle; i < this->iMaxParticles; ++i)
	{
		if (this->listOfParticles[i].fLife < 0) {
			this->iLastUsedParticle = i;
			return i;
		}
	}

	for (int i = 0; i < iLastUsedParticle; ++i)
	{
		if (this->listOfParticles[i].fLife < 0) {
			this->iLastUsedParticle = i;
			return i;
		}
	}

	return 0;
}

void ParticleSystemModel::SortParticles()
{
	std::sort(&this->listOfParticles[0], &this->listOfParticles[this->iMaxParticles]);
}

void ParticleSystemModel::OnLoop(double dDeltaTime)
{
	this->ptrEmitter->OnLoop(dDeltaTime);

	int newparticles = (int)(dDeltaTime*10000.0);
	if (newparticles > (int)(0.016f*10000.0))
		newparticles = (int)(0.016f*10000.0);


	glm::vec3 CameraPosition(glm::inverse(ptrController->getViewMatrix())[3]);

	for (int i = 0; i < newparticles; i++) {
		int particleIndex = FindUnusedParticle();

		// Create New Particle
		this->fnOnParticleBirth(dDeltaTime, &this->listOfParticles[particleIndex], this);

	}
	ParticlesCount = 0;

	for (int i = 0; i < this->iMaxParticles; i++) {

		Particle& p = this->listOfParticles[i]; // shortcut

		if (p.fLife > 0.0f) {

			// Decrease life
			p.fLife -= dDeltaTime;
			if (p.fLife > 0.0f) {
				this->fnOnParticleLoop(dDeltaTime, &p, this);

				p.fCameraDist = glm::length2(p.vPosition - CameraPosition);

				// Fill the GPU buffer
				this->ptrfParticlePositionSizeData[4 * ParticlesCount + 0] = p.vPosition.x;
				this->ptrfParticlePositionSizeData[4 * ParticlesCount + 1] = p.vPosition.y;
				this->ptrfParticlePositionSizeData[4 * ParticlesCount + 2] = p.vPosition.z;
				this->ptrfParticlePositionSizeData[4 * ParticlesCount + 3] = p.fSize;

				this->ptrfParticleColorData[4 * ParticlesCount + 0] = p.cR;
				this->ptrfParticleColorData[4 * ParticlesCount + 1] = p.cG;
				this->ptrfParticleColorData[4 * ParticlesCount + 2] = p.cB;
				this->ptrfParticleColorData[4 * ParticlesCount + 3] = p.cA;

			}
			else {
				// Particles that just died will be put at the end of the buffer in SortParticles();
				this->fnOnParticleDeath(dDeltaTime, &p, this);
			}

			ParticlesCount++;

		}
	}

	SortParticles();

	glBindBuffer(GL_ARRAY_BUFFER, this->uiPositionBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->iMaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLfloat) * 4, this->ptrfParticlePositionSizeData);

	glBindBuffer(GL_ARRAY_BUFFER, this->uiColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->iMaxParticles * 4 * sizeof(GLubyte), NULL, GL_STREAM_DRAW); // Buffer orphaning, a common way to improve streaming perf. See above link for details.
	glBufferSubData(GL_ARRAY_BUFFER, 0, ParticlesCount * sizeof(GLubyte) * 4, this->ptrfParticleColorData);
}

void ParticleSystemModel::OnRender()
{

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, this->uiVertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : positions of particles' centers
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, this->uiPositionBuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		4,                                // size : x + y + z + size => 4
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : particles' colors
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, this->uiColorBuffer);
	glVertexAttribPointer(
		2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		4,                                // size : r + g + b + a => 4
		GL_UNSIGNED_BYTE,                 // type
		GL_TRUE,                          // normalized?    *** YES, this means that the unsigned char[4] will be accessible with a vec4 (floats) in the shader ***
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, this->uiUVBufferId);
	glVertexAttribPointer(
		3,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// These functions are specific to glDrawArrays*Instanced*.
	// The first parameter is the attribute buffer we're talking about.
	// The second parameter is the "rate at which generic vertex attributes advance when rendering multiple instances"
	// http://www.opengl.org/sdk/docs/man/xhtml/glVertexAttribDivisor.xml

	glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
	glVertexAttribDivisor(1, 1); // positions : one per quad (its center)                 -> 1
	glVertexAttribDivisor(2, 1); // color : one per quad                                  -> 1
	glVertexAttribDivisor(3, 0); // particles vertices : always reuse the same 4 vertices -> 0

	glDrawArraysInstanced(GL_TRIANGLES, 0, this->sizeModel, ParticlesCount);

	glVertexAttribDivisor(0, 0); // particles vertices : always reuse the same 4 vertices -> 0
	glVertexAttribDivisor(1, 0); // positions : one per quad (its center)                 -> 1
	glVertexAttribDivisor(2, 0); // color : one per quad                                  -> 1
	glVertexAttribDivisor(3, 0); // particles vertices : always reuse the same 4 vertices -> 0
}

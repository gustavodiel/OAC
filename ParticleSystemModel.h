#pragma once
#include <glm/glm.hpp>
#include <gl/glew.h>

#include <functional>
#include "ParticleSystem.h"

class ParticleSystemModel : public ParticleSystem
{

private:
	int							iMaxParticles;
	int							iLastUsedParticle = 0;
	int							ParticlesCount;

	unsigned int				uiTextureId;

	Particle*					listOfParticles;

	const char*					cTextureName;

	std::function<void(double, Particle*, ParticleSystemModel*)>				fnOnParticleLoop;
	std::function<void(double, Particle*, ParticleSystemModel*)>				fnOnParticleBirth;
	std::function<void(double, Particle*, ParticleSystemModel*)>				fnOnParticleDeath;

	GLfloat*					ptrfParticlePositionSizeData;
	GLubyte*					ptrfParticleColorData;

	GLuint						uiVertexBuffer;
	GLuint						uiUVBufferId;			//!< id do buffer de UVs
	GLuint						uiPositionBuffer;
	GLuint						uiColorBuffer;

	class Entity*				ptrEmitter;

	int sizeModel = 0;

public:
	ParticleSystemModel(): ParticleSystem() {};
	ParticleSystemModel(const char* tex, int iMaxParticles = 1000, glm::vec3 vStartingPos = glm::vec3(0, 0, -20), glm::vec3 vStartingDir = glm::vec3(0, 10, 0));
	~ParticleSystemModel();

	int FindUnusedParticle();

	void SortParticles();

	void OnLoop(double dDeltaTime);

	Entity* GetEmitter() { return this->ptrEmitter; };

	void SetOnLoopFunction(std::function<void(double, Particle*, ParticleSystemModel*)> fun) { this->fnOnParticleLoop = fun; };
	void SetBirthFunction(std::function<void(double, Particle*, ParticleSystemModel*)> fun) { this->fnOnParticleBirth = fun; };
	void SetDeathFunction(std::function<void(double, Particle*, ParticleSystemModel*)> fun) { this->fnOnParticleDeath = fun; };

	void OnRender();
};



#pragma once

#include <glm/glm.hpp>
#include <gl/glew.h>

#include <functional>

class ParticleSystem
{
public:

	/* PARTICLE SETTINGS */
	typedef struct Particle {
		glm::vec3				vPosition;
		glm::vec3				vSpeed;

		unsigned char			cR;
		unsigned char			cG;
		unsigned char			cB;
		unsigned char			cA;

		float					fSize;
		float					fAngle;
		float					fWeigth;
		float					fLife;
		float					fTotalLife;
		float					fCameraDist;

		int						iIndex;

		bool operator < (const Particle& that) const {
			return this->fCameraDist > that.fCameraDist;
		}

	} Particle;

private:
	int							iMaxParticles;
	int							iLastUsedParticle = 0;
	int							ParticlesCount;

	unsigned int				uiTextureId;

	Particle*					listOfParticles;

	const char*					cTextureName;

	std::function<void(double, Particle*, ParticleSystem*)>				fnOnParticleLoop;
	std::function<void(double, Particle*, ParticleSystem*)>				fnOnParticleBirth;
	std::function<void(double, Particle*, ParticleSystem*)>				fnOnParticleDeath;

	GLfloat*					ptrfParticlePositionSizeData;
	GLubyte*					ptrfParticleColorData;

	GLuint						uiVertexBuffer;
	GLuint						uiPositionBuffer;
	GLuint						uiColorBuffer;

	class Entity*				ptrEmitter;

public:
	ParticleSystem() {};
	ParticleSystem(const char* tex, int iMaxParticles = 1000, glm::vec3 vStartingPos = glm::vec3(0,0,-20), glm::vec3 vStartingDir = glm::vec3(0,10,0));
	~ParticleSystem();

	virtual int FindUnusedParticle();

	virtual void SortParticles();

	virtual void OnLoop(double dDeltaTime);

	virtual Entity* GetEmitter() { return this->ptrEmitter; };

	virtual void SetEmitter(Entity* ent) { this->ptrEmitter = ent; };

	virtual void SetOnLoopFunction(std::function<void(double, Particle*, ParticleSystem*)> fun) { this->fnOnParticleLoop = fun; };
	virtual void SetBirthFunction(std::function<void(double, Particle*, ParticleSystem*)> fun) { this->fnOnParticleBirth = fun; };
	virtual void SetDeathFunction(std::function<void(double, Particle*, ParticleSystem*)> fun) { this->fnOnParticleDeath = fun; };

	virtual void OnRender();
};


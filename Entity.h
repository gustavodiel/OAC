#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <Windows.h>
#include <gl/glew.h>

#include <string>
#include <vector>

#include "BulletCollision/CollisionShapes/btCollisionShape.h"
#include "BulletDynamics/Dynamics/btRigidBody.h"

using namespace glm;

class Entity
{
protected:
	glm::vec3 vTranslate,			//!< vetor translacao em coordenadas locais
		vRotate,					//!< angulos de rotacao em relacao a cada eixo cartesiano
		vRotatePivot,				//!< angulos de rotaçao em relaçao ao pivot da entidade
		vScale,						//!< fatores de escala em relacao a cada eixo cartesiano
		vPivot,						//!< ponto de referencia do sistema de coordenadas para esta entidade
		vMinValue,					//!< Ponto minimo da mesh
		vMaxValue,					//!< ponto maximo da mesh
		vCenter,					//!< centro da mesh
		vDimensionSize;				//!< dimensoes da mesh

	std::vector<Entity*>			listOfEntities;		//!< lista de ponteiros para entidades que compoem este objeto


	glm::quat						qOrientation;		//!< Quaternation da orientacao
	btCollisionShape*				ptrCollisionShape;
	btRigidBody*					ptrBulletRigidBody;
	glm::vec3						v3Intertia;
	bool							isStatic = false;
	float							fMass;
	float							fRadius;

	std::string						sName;

	glm::mat4						m4DepthMVP;							//!< matrix de MVP
	glm::mat4						m4ModelMatrix;						//!< matrix do model ( para aplicar as tranformacoes )
	
	Entity*							ptrRoot;				//!< Entidade raiz da entidade. NULL se nao tiver

	class Animator*					ptrAnimator;		//!< ponteiro para o objeto animador de atributos associado a este ator

	class Vehicle*					ptrVehicle;				//!< ponteiro para o veiculo ( steering behaviour )

	bool							bIsWireframe = false;					//!< renderizar como wireframe?

public:
	bool	bHasLoadedDimensions = false;			//!< ja executou a funcao LoadDinensions()?
	bool	bDeletable = true;

	enum CollisionType
	{
		PLANE = 0,
		SPHERE,
		BOX
	};

public:
	Entity();
	Entity(const Entity&);
	Entity(Entity*);

	/**
	\brief Rotina de renderizacao da sombra do objeto em OPENGL.<p>Esta rotina deve
	ser sobrecarregada para cada tipo de entidade em particular.
	*/
	virtual void OnPreRender(glm::mat4);

	/**
	\brief Rotina de renderizacao do objeto em OPENGL.<p>Esta rotina deve
	ser sobrecarregada para cada tipo de entidade em particular.
	*/
	virtual void OnRender(glm::mat4);

	virtual void setTranslate(glm::vec3 vec);
	virtual void setRoot(Entity* ent);
	virtual void setPhysicTranslate(glm::vec3 pos);
	virtual void setRotate(glm::vec3 vec);
	virtual void setOrientation(glm::quat ori);
	virtual void setRotatePivot(glm::vec3 vec);
	virtual void setScale(glm::vec3 vec);
	virtual void setPivot(glm::vec3 vec);

	virtual void setStatic(bool is) { this->isStatic = is; this->fMass = is ? 0.0f : 1.0f; };
	virtual void setMass(float mass) { this->fMass = mass; };
	void ActivatePhysics(CollisionType);
	void ApplyForce(vec3 force);

	virtual void LoadDimensions();

	virtual void setName(std::string name) { this->sName = name; };

	inline virtual vec3 GetDimensions() { return vMaxValue - vMinValue; }
	inline virtual vec3 GetMinValue() { return vMinValue; }
	inline virtual vec3 GetMaxValue() { return vMaxValue; }
	inline virtual vec3 GetCenter() { return vCenter; }
	inline virtual vec3 GetDimensionSize() { return vDimensionSize; }
	inline virtual vec3 GetWorldPosition() { return ptrRoot != NULL ? ptrRoot->getTranslate() + vTranslate : vTranslate; };


	/**
	\brief Retorna o valor corrente da posicao do objeto
	\return Vector3 com o valor atual do vetor translacao
	*/
	inline glm::vec3 getTranslate() { return this->vTranslate; }
	/**
	\brief Retorna o valor corrente da orientacao do objeto
	\return Vector3 com o valor atual do vetor rotacao
	*/
	inline glm::vec3 getRotate() { return this->vRotate; }
	/**
	\brief Retorna o valor corrente da orientacao do objeto
	\return Vector3 com o valor atual do vetor rotacao
	*/
	inline glm::quat getOrientation() { return this->qOrientation; }
	/**
	\brief Retorna o valor corrente da orientacao do objeto em relaçao ao pivot
	\return Vector3 com o valor atual do vetor rotacao
	*/
	inline glm::vec3 getRotatePivot() { return this->vRotatePivot; }
	/**
	\brief Retorna o valor corrente do tamanho do objeto
	\return Vector3 com o valor atual do vetor escala
	*/
	inline glm::vec3 getScale() { return this->vScale; }
	/**
	\brief Retorna o valor corrente do pivot do objeto
	\return Vector3 com o valor atual do vetor pivot
	*/
	inline glm::vec3 getPivot() { return this->vPivot; }
	/**
	\brief Rotina de renderizacao do objeto em OPENGL.<p>Esta rotina deve
	ser sobrecarregada para cada tipo de entidade em particular.
	*/
	//virtual void OnRender() = 0; // metodo abstrato: precisa ser implementado em uma classe-filha
								 /**
								 \brief Rotina de atualizacao dos parametros animaveis do objeto.<p>
								 Esta rotina deve ser sobrecarregada para cada tipo de entidade em
								 particular.
								 */
	virtual void OnLoop(double); // metodo abstrato: precisa ser implementado em uma classe-filha

	/**
	\brief Retorna a referencia ao objeto corpo rigido associado a este Entity
	\return ponteiro para o objeto RigidBody associado
	*/
	inline btRigidBody* getRigidBody() { return this->ptrBulletRigidBody; }

	inline bool hasRigidBody() { return this->ptrBulletRigidBody != NULL; };

	/**
	\brief Ativa ou desativa o wireframe view para o modelo
	\param wire booleana se esta ou nao ativado o wireframe
	*/
	void SetWireframe(bool wire) { this->bIsWireframe = wire; };

	/* ANIMATION STUFF */
	virtual void Initialize() {};
	void setAnimator(class Animator *);
	/**
	\brief Retorna a referencia ao objeto animador associado a este objeto
	\return ponteiro para o objeto animador
	*/
	inline class Animator * getAnimator() { return this->ptrAnimator; }

	inline void setVehicle(Vehicle* veh) { this->ptrVehicle = veh; };

	void AddEntity(Entity* ent);
	void DelEntity(Entity* ent);

};
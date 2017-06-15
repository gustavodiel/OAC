#include "stdafx.h"
#include "Entity.h"

#include <sstream>

#include <glm\glm.hpp>
#include "LinearMath\btDefaultMotionState.h"

#include "Constants.h"
#include "BulletHandler.h"
#include "Utilities.hpp"
#include "Animator.h"
#include "Vehicle.h"

using namespace glm;
/**
\brief Construtor para a classe Entity
Cria uma entidade posicionada na origem, orientada sobre os eixos cartesianos e
em escala canonica.
*/
Entity::Entity()
{
	this->setTranslate(vec3(0.0f, 0.0f, 0.0f));
	this->setRotate(vec3(0.0f, 0.0f, 0.0f));
	this->setRotatePivot(vec3(0.0f, 0.0f, 0.0f));
	this->setScale(vec3(1.0f, 1.0f, 1.0f));
	this->setPivot(vec3(0.0f, 0.0f, 0.0f));
	this->vMaxValue = vec3( -9999.0f, -9999.0f, -9999.0f);
	this->vMinValue = -this->vMaxValue;
	std::ostringstream sstr;
	sstr << "Entity:" << ptrApp->getEntityCount();

	this->setName(sstr.str());
}
/**
\brief Construtor de clonagem para a classe Entity
Cria uma copia exata de um objeto entidade ja existente
\param clone Objeto a ser clonado
*/
Entity::Entity(const Entity& clone)
{
	this->setTranslate(clone.vTranslate);
	this->setRotate(clone.vRotate);
	this->setRotatePivot(clone.vRotatePivot);
	this->setScale(clone.vScale);
	this->setPivot(clone.vPivot);

}
/**
\brief Construtor de clonagem para a classe Entity a partir de ponteiros
Cria uma copia exata de um objeto entidade ja existente
\param ptrClone Ponteiro para o objeto a ser clonado
*/
Entity::Entity(Entity* ptrClone)
{
	this->setTranslate(ptrClone->vTranslate);
	this->setRotate(ptrClone->vRotate);
	this->setRotatePivot(ptrClone->vRotatePivot);
	this->setScale(ptrClone->vScale);
	this->setPivot(ptrClone->vPivot);
}
void Entity::ActivatePhysics(CollisionType type) {

	this->LoadDimensions();
	//btVector3 box(this->vMaxValue.x / 2., this->vMaxValue.y / 2., this->vMaxValue.z / 2.);
	btVector3 box(this->vMaxValue.x, this->vMaxValue.y, this->vMaxValue.z);

	//btVector3 box(this->vDimensionSize.x / 2.0, this->vDimensionSize.y/2, this->vDimensionSize.z / 2.0);

	btVector3 pos(GetWorldPosition().x, GetWorldPosition().y, GetWorldPosition().z);
	btQuaternion ori(this->qOrientation.x, this->qOrientation.y, this->qOrientation.z, this->qOrientation.w);

	btDefaultMotionState* motionstate;
	switch (type)
	{
	case Entity::PLANE:
		//box = btVector3(32, 1, 32);
		this->ptrCollisionShape = new btBoxShape(box);
		motionstate = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), pos));
		break;
	case Entity::SPHERE:
		this->ptrCollisionShape = new btSphereShape(this->fRadius / 2.0f);
		motionstate = new btDefaultMotionState(btTransform(
			ori,
			pos
		));
		break;
	case Entity::BOX:
		this->ptrCollisionShape = new btBoxShape(box);
		motionstate = new btDefaultMotionState(btTransform(
			ori,
			pos
		));
		break;
	default:
		this->ptrCollisionShape = new btBoxShape(box);
		motionstate = new btDefaultMotionState(btTransform(
			ori,
			pos
		));
		break;
	}

	btVector3 totalInertia(0,0,0);
	if (!this->isStatic) {
		this->ptrCollisionShape->calculateLocalInertia(this->fMass, totalInertia);
	}

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
		this->fMass,                  // mass, in kg. 0 -> Static object, will never move.
		motionstate,
		this->ptrCollisionShape,  // collision shape of body
		totalInertia    // local inertia
	);

	rigidBodyCI.m_restitution = 0.4;	

	ptrBulletRigidBody = new btRigidBody(rigidBodyCI);
	ptrBulletRigidBody->setDamping(0.3, 0.9);

	ptrBulletHandler->AddRigidBody(ptrBulletRigidBody);

	ptrBulletRigidBody->setUserPointer((void*)this);


}

/**
\brief Carrega as dimensoes do modelo
*/
void Entity::LoadDimensions() {

	this->vMaxValue = vec3(-9999.0f, -9999.0f, -9999.0f);
	this->vMinValue = -this->vMaxValue;

	for (vector<Entity*>::iterator pointer = this->listOfEntities.begin(); pointer != this->listOfEntities.end(); pointer++) {
		if (!(*pointer)->bHasLoadedDimensions) {
			(*pointer)->LoadDimensions();
		}
		vec3 minChild = (*pointer)->GetMinValue();
		vec3 maxChild = (*pointer)->GetMaxValue();
		if (vMinValue.x > minChild.x) vMinValue.x = minChild.x;
		if (vMinValue.y > minChild.y) vMinValue.y = minChild.y;
		if (vMinValue.z > minChild.z) vMinValue.z = minChild.z;
		if (vMaxValue.x < maxChild.x) vMaxValue.x = maxChild.x;
		if (vMaxValue.y < maxChild.y) vMaxValue.y = maxChild.y;
		if (vMaxValue.z < maxChild.z) vMaxValue.z = maxChild.z;
	}

	vMaxValue.x *= this->vScale.x;
	vMaxValue.y *= this->vScale.y;
	vMaxValue.z *= this->vScale.z;

	vMinValue.x *= this->vScale.x;
	vMinValue.y *= this->vScale.y;
	vMinValue.z *= this->vScale.z;

	vCenter = (vMaxValue + vMinValue) / 2.0f;

	vDimensionSize = vMaxValue - vMinValue;

	bHasLoadedDimensions = true;
}

void Entity::AddEntity(Entity* ent)
{
	this->listOfEntities.push_back(ent);
	ent->setRoot(this);
}

void Entity::ApplyForce(vec3 force)
{
	this->ptrBulletRigidBody->applyCentralImpulse(btVector3(force.x, force.y, force.z));
}

/**
\brief Define a posicao espacial para o objeto (em coordenadas locais)
\param vec coordenadas do vetor translacao
*/
void Entity::setTranslate(vec3 vec)
{
	this->vTranslate = vec;	
}

void Entity::DelEntity(Entity* ent) {
	auto i = this->listOfEntities.begin();

	while (i != this->listOfEntities.end()) {
		// Do some stuff
		if (ent == *i) {
			ent->setRoot(NULL);
			i = this->listOfEntities.erase(i);
			break;
		}
		else
			++i;
	}
}

void Entity::setRoot(Entity* ent)
{
	this->ptrRoot = ent;
}

void Entity::setPhysicTranslate(glm::vec3 vec)
{
	if (this->hasRigidBody()) {
		this->ptrBulletRigidBody->translate(btVector3(vec.x, vec.y, vec.z));
	}
}

/**
\brief Define orientacao espacial para o objeto (em coordenadas locais)
\param vec coordenadas do vetor orientacao
*/
void Entity::setRotate(vec3 vec)
{
	this->vRotate = vec;
	qOrientation = quat(vec3(glm::radians(this->vRotate.x), glm::radians(this->vRotate.y), glm::radians(this->vRotate.z)));
}

void Entity::setOrientation(glm::quat ori)
{
	this->qOrientation = ori;
}

/**
\brief Define orientacao espacial para o objeto (em coordenadas locais)
\param vec coordenadas do vetor orientacao
*/
void Entity::setRotatePivot(vec3 vec)
{
	this->vRotatePivot = vec;
}
/**
\brief Define o tamanho do objeto (em coordenadas locais)
\param vec fatores de escala para o objeto
*/
void Entity::setScale(vec3 vec)
{
	this->vScale = vec;
}
/**
\brief Define a posição do pivot do objeto (em coordenadas locais)
\param vec coordenadas para o pivot do objeto
*/
void Entity::setPivot(vec3 vec)
{
	this->vPivot = vec;
}

/**
\brief Rotina de atualizacao dos parametros animaveis do objeto.<p>
Esta rotina deve ser sobrecarregada para cada tipo de entidade em particular.
*/
void Entity::OnLoop(double dDeltaTime)
{
	if (this->ptrBulletRigidBody && !this->isStatic) {
		btTransform btTransformation;
		this->ptrBulletRigidBody->getMotionState()->getWorldTransform(btTransformation);
		btQuaternion rotation = btTransformation.getRotation();
		btVector3 transform = btTransformation.getOrigin();
		this->setTranslate(vec3({ transform.getX(), transform.getY(), transform.getZ() }));
		//this->setOrientation(quat({ btTransformation.getRotation().getX(), btTransformation.getRotation().getY(), btTransformation.getRotation().getZ(), btTransformation.getRotation().getW() }));
		this->setOrientation(angleAxis(rotation.getAngle(), vec3(rotation.getAxis().getX(), rotation.getAxis().getY(), rotation.getAxis().getZ())));
	}

	if (this->ptrAnimator) {
		this->ptrAnimator->OnLoop(dDeltaTime);
	}

	if (this->ptrVehicle) {
		this->ptrVehicle->OnLoop(dDeltaTime);
	}
}
/**
\brief Rotina de renderizacao de sombra do objeto em OPENGL.
*/
void Entity::OnPreRender(glm::mat4 _ModelMatrix) {

	m4ModelMatrix = glm::rotate(_ModelMatrix, glm::radians(this->vRotatePivot.z), glm::vec3(0.0f, 0.0f, 1.0f));
	m4ModelMatrix = glm::rotate(m4ModelMatrix, glm::radians(this->vRotatePivot.y), glm::vec3(0.0f, 1.0f, 0.0f));
	m4ModelMatrix = glm::rotate(m4ModelMatrix, glm::radians(this->vRotatePivot.x), glm::vec3(1.0f, 0.0f, 0.0f));

	m4ModelMatrix = glm::translate(m4ModelMatrix, this->vPivot);
	m4ModelMatrix = glm::translate(m4ModelMatrix, this->vTranslate) * glm::toMat4(this->qOrientation);

	/*m4ModelMatrix = glm::rotate(m4ModelMatrix, glm::radians(this->vRotate.z), glm::vec3(0.0f, 0.0f, 1.0f));
	m4ModelMatrix = glm::rotate(m4ModelMatrix, glm::radians(this->vRotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
	m4ModelMatrix = glm::rotate(m4ModelMatrix, glm::radians(this->vRotate.x), glm::vec3(1.0f, 0.0f, 0.0f));*/

	m4ModelMatrix = glm::scale(m4ModelMatrix, this->vScale);
	m4ModelMatrix = glm::translate(m4ModelMatrix, this->vPivot * -1.0f);

	for (vector<Entity*>::iterator pointer = this->listOfEntities.begin(); pointer != this->listOfEntities.end(); pointer++) {
		(*pointer)->OnPreRender(m4ModelMatrix);
	}
}

/**
\brief Rotina de renderizacao do objeto em OPENGL.
*/
void Entity::OnRender(glm::mat4 _ModelMatrix)
{
	for (vector<Entity*>::iterator pointer = this->listOfEntities.begin(); pointer != this->listOfEntities.end(); pointer++)
		(*pointer)->OnRender(m4ModelMatrix);
}
/**
\brief Associa um objeto animador com este ator
\param ptrAnimator ponteiro do objeto animador a ser associado
*/
void Entity::setAnimator(Animator* ptrAnimator)
{
	if (ptrAnimator)
	{
		this->ptrAnimator = ptrAnimator;
		this->ptrAnimator->setParent(this);
	}
}

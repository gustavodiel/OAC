#pragma once

/* STL Includes */
#include <vector>

/* Bullet Includes */
#include <btBulletDynamicsCommon.h>

/* GLM Includes */
#include <glm/glm.hpp>


class BulletHandler
{
protected:
	btBroadphaseInterface*					ptrBradphase;

	// Set up the collision configuration and dispatcher
	btDefaultCollisionConfiguration*		ptrCollisionConfiguration;
	btCollisionDispatcher*					ptrCollisionDispatcher;

	btSequentialImpulseConstraintSolver*	ptrSolver;

	btDiscreteDynamicsWorld*				ptrWorld;

	std::vector<btRigidBody*>				ptrRigidBodies;
public:
	BulletHandler(glm::vec3 v3Gravity);
	~BulletHandler();

	void OnUpdate(double dDeltaTime);


	inline btDiscreteDynamicsWorld* GetWorld() { return this->ptrWorld; };

	void AddRigidBody(btRigidBody*);


};


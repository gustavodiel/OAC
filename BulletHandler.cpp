#include "stdafx.h"
#include "BulletHandler.h"

#include "Constants.h"
#include "DebugDraw.h"


BulletHandler::BulletHandler(glm::vec3 v3Gravity)
{
	this->ptrBradphase = new btDbvtBroadphase();
	this->ptrCollisionConfiguration = new btDefaultCollisionConfiguration();
	this->ptrCollisionDispatcher = new btCollisionDispatcher(this->ptrCollisionConfiguration);
	this->ptrSolver = new btSequentialImpulseConstraintSolver;

	// The world.
	this->ptrWorld = new btDiscreteDynamicsWorld(
		this->ptrCollisionDispatcher,
		this->ptrBradphase,
		this->ptrSolver,
		this->ptrCollisionConfiguration
	);

	this->ptrWorld->setGravity(btVector3(v3Gravity.x, v3Gravity.y, v3Gravity.z));
}


BulletHandler::~BulletHandler()
{
	delete ptrWorld;
	delete ptrCollisionConfiguration;
	delete ptrSolver;
	delete ptrBradphase;
	delete ptrCollisionDispatcher;
}

void BulletHandler::OnUpdate(double dDeltaTime)
{
	this->ptrWorld->stepSimulation(dDeltaTime, 0);
	this->ptrWorld->setDebugDrawer(ptrDebugger);
	//this->ptrWorld->debugDrawWorld();
}

void BulletHandler::AddRigidBody(btRigidBody* rb)
{
	this->ptrWorld->addRigidBody(rb);
	this->ptrRigidBodies.push_back(rb);
}

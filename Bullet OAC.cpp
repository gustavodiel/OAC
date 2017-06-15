/************************************************************************/
/* File: TesteGL.cpp                                                    */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

/* Basic Include */
#include "stdafx.h"

/* Standard Includes */
#include <Windows.h>
#include <stdlib.h>
#include <ctime>
#include <vector>

/* Utility Includes */
#include "Application.h"
#include "PerlinNoise.h"
#include "Animator.h"
#include "Utilities.hpp"
#include "BulletHandler.h"

/* Interpolates Includes */
#include "Interpolator.h"
#include "LinearInterpolator.h"
#include "BlockingInterpolator.hpp"
#include "PolinomialInterpolator.hpp"
#include "PolynomInterpolator.h"

/* OBJ Includes */
#include "Model.h"
#include "Fence.h"
#include "Tree.h"
#include "Barn.hpp"

/* Actor Includes */
#include "Carro.hpp"
#include "Robot.h"
#include "Cubo.h"
#include "Camera.h"
#include "Light.h"

/* Articulated Actors Includes */
#include "Headphone.h"
#include "Peao.h"
#include "Pessoa.h"
#include "BodyMember.h"
#include "Cow.h"
#include "Dama.h"

/* Physics Includes */
#include "Cloth.h"
#include "BillBoard.h"
#include "Cloud.h"

/* Particles Includes */
#include "ParticleSystem.h"
#include "ParticleSystemModel.h"
#include "Emitter.h"

/* Steering Behaviour */
#include "Vehicle.h"
#include "IBehaviour.h"
#include "SeekBehaviour.h"
#include "AvoidBoidBehaviour.h"
#include "AvoidObstacleBehaviour.h"
#include "WanderBehaviour.h"

/* GLM Includes */
#include <glm/glm.hpp>
#include "StayWithin.h"
#include "Dove.h"


using namespace glm;

Application* ptrApp;

int main()
{
	ptrApp = new Application(2560, 1440);

	std::vector<Entity*> arvores;

	// **********************************************************
	//                               GROUND
	// **********************************************************

	/* Grama */
	int groundSquareAmount = 16;
	int sizeGrid = 64;
	for (int i = 0; i < groundSquareAmount; ++i) {
		for (int k = 0; k < groundSquareAmount; ++k) {
			Model * ptrGround = new Model("objs/box.obj", "textures/grass_01.jpg");
			float sizeGrd = (float)sizeGrid / groundSquareAmount;
			ptrGround->setScale(vec3(sizeGrd, 0.5f, sizeGrd));
			ptrGround->setTranslate(vec3(i * sizeGrd - sizeGrid / 2.0f, -0.4, k *sizeGrd - sizeGrid / 2.0f));
			ptrGround->getMaterial()->SetSpecularColor(0.0, 0.0, 0.0);

			ptrGround->setStatic(true);
			ptrGround->ActivatePhysics(Entity::PLANE);

			ptrApp->AddEntity(ptrGround);
		}
	}

	/*
		int groundSquareAmount = 1;
	for (int i = 0; i < groundSquareAmount; ++i) {
		for (int k = 0; k < groundSquareAmount; ++k) {
			Model * ptrGround = new Model("objs/box.obj", "textures/grass_01.jpg");
			ptrGround->setScale(vec3(32 - groundSquareAmount / 2.0f, 0.01f, 32 - groundSquareAmount / 2.0f));
			ptrGround->setTranslate(vec3(i * groundSquareAmount / 2.0f - groundSquareAmount * 2.0f, 0, 2 + k * groundSquareAmount / 2.0f - groundSquareAmount * 2.0f));
			ptrGround->getMaterial()->SetSpecularColor(0.0, 0.0, 0.0);

			ptrGround->setStatic(true);
			ptrGround->ActivatePhysics(Entity::PLANE);

			ptrApp->AddEntity(ptrGround);
		}
	}
	*/

	/* Rua */
	for (int i = 0; i < 16; ++i) {
		Model* ptrRoad = new Model("objs/box.obj", "textures/dirt_01.jpg");
		ptrRoad->setScale(vec3(2.0f, 0.1f, 2.0f));
		ptrRoad->setTranslate(vec3(i * 2 - 16, 0, -2.5));
		ptrRoad->getMaterial()->SetSpecularColor(0.0, 0.0, 0.0);

		ptrRoad->setStatic(true);
		ptrRoad->ActivatePhysics(Entity::PLANE);

		ptrApp->AddEntity(ptrRoad);
	}

	/* Calcada */
	for (int i = 0; i < 16; ++i) {
		Model* ptrRoad = new Model("objs/box.obj", "textures/concrete_01.jpg");
		ptrRoad->setScale(vec3(2.0f, 0.2f, 1.0f));
		ptrRoad->setTranslate(vec3(i * 2 - 16, 0, -1));

		ptrRoad->setStatic(true);
		ptrRoad->ActivatePhysics(Entity::PLANE);

		ptrApp->AddEntity(ptrRoad);
	}

	for (int i = 0; i < 16; ++i) {
		Model* ptrRoad = new Model("objs/box.obj", "textures/concrete_01.jpg");
		ptrRoad->setScale(vec3(2.0f, 0.2f, 1.0f));
		ptrRoad->setTranslate(vec3(i * 2 - 16, 0, -4));
		ptrRoad->setStatic(true);
		ptrRoad->ActivatePhysics(Entity::PLANE);

		ptrApp->AddEntity(ptrRoad);
	}


	// **********************************************************
	//                                CERCA
	// **********************************************************
	for (int i = 0; i < 5; ++i) {
		Fence * ptrFence = new Fence();
		ptrFence->Initialize(&arvores);
		ptrFence->setTranslate(vec3(5 - i * 4, 0, -0.5f));
		ptrFence->setScale(vec3(1, 0.5f, 1.0f));
		ptrApp->AddEntity(ptrFence);

		arvores.push_back(ptrFence);

		ptrFence->setStatic(true);
		ptrFence->ActivatePhysics(Entity::BOX);

	}

	// **********************************************************
	//                                ARVORES
	// **********************************************************
	Tree * ptrTree = new Tree();
	ptrTree->setTranslate(vec3(2.0f, 0.0f, 2.0f));
	ptrTree->setPivot(vec3(0.0f, 1.0f, 0.0f));
	ptrTree->setRotate(vec3(0.0f, 0.0f, 0.0f));
	ptrApp->AddEntity(ptrTree);
	for (int i = 0; i < 32; ++i) {
		ptrTree = new Tree();
		ptrTree->setTranslate(vec3(rand() % 32 - 16, 0.0f, 5 + rand() % 16));
		ptrTree->setPivot(vec3(0.0f, 1.0f, 0.0f));
		ptrTree->setRotate(vec3(0.0f, 0.0f, 0.0f));
		ptrApp->AddEntity(ptrTree);

		arvores.push_back(ptrTree);

		if (rand() % 3 <= 1) {
			for (int i = 0; i < rand() % 7 + 2; ++i) {
				Model* apple = new Model("objs/apple.obj", "textures/apple.png");
				apple->setScale(vec3(0.1f, 0.1f, 0.1f));
				apple->setTranslate(vec3(rand() % 20 / 10.0f - 1.0f, 1.25f, rand() % 20 / 10.0f - 1.0f) + ptrTree->getTranslate());
				ptrApp->AddEntity(apple);

				ptrApp->AddTimerFunction([apple](double deltaTime) {
					apple->setMass(0.5);
					apple->ActivatePhysics(Entity::SPHERE);
				}, rand() % 20 * 1.0f);

			}
		}
	}

	Tree * ptrTree1 = new Tree();
	ptrTree1->setTranslate(vec3(2.9f, 0.0f, -5.2f));
	ptrApp->AddEntity(ptrTree1);

	Tree * ptrTree2 = new Tree();
	ptrTree2->setTranslate(vec3(-1.0f, 0.0f, -0.0f));
	ptrTree2->setScale(vec3(0.5f, 0.5f, 0.5f));
	ptrApp->AddEntity(ptrTree2);

	arvores.push_back(ptrTree);
	arvores.push_back(ptrTree1);
	arvores.push_back(ptrTree2);


	// **********************************************************
	//                                CASA
	// **********************************************************
	Barn * ptrBarn = new Barn();
	ptrBarn->setTranslate(vec3(-2.2f, 0.0f, 5.0f));
	ptrBarn->setRotate(vec3(0, 90, 0));
	//ptrBarn->setScale(vec3(1.85f, 1.3f, 3.0f));
	ptrBarn->Initialize();
	ptrApp->AddEntity(ptrBarn);

	arvores.push_back(ptrBarn);

	// **********************************************************
	//                            ACTOR: PESSOAS CORRENDO
	// **********************************************************
	/*
	Interpolator * ptrInterpolatorPessoa1Translate = new PolinomialInterpolator(PolinomialInterpolator::Catmullrom);

	ptrInterpolatorPessoa1Translate->addAttribute(new AttrVector3(vec3(3.5f, 0.0f, -0.6f), 0.0f, PoseAttr::TRANSLATE)); // tempo: 0 seg
	ptrInterpolatorPessoa1Translate->addAttribute(new AttrVector3(vec3(3.5f, 0.0f, -0.6f), 20.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrInterpolatorPessoa1Translate->addAttribute(new AttrVector3(vec3(9.0f, 0.0f, -0.8f), 21.5f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrInterpolatorPessoa1Translate->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), 0.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa1Translate->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), 11.5f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa1Translate->addAttribute(new AttrVector3(vec3(0.0f, 40.0f, 0.0f), 12.5f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa1Translate->addAttribute(new AttrVector3(vec3(0.0f, -40.0f, 0.0f), 13.5f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa1Translate->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), 14.0f, PoseAttr::ROTATE)); // tempo: 1 seg

	ptrInterpolatorPessoa1Translate->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), 18.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa1Translate->addAttribute(new AttrVector3(vec3(0.0f, 75.0f, 0.0f), 18.4f, PoseAttr::ROTATE)); // tempo: 1 seg

	ptrInterpolatorPessoa1Translate->addAttribute(new AttrVector3(vec3(0.0f, 75.0f, 0.0f), 20.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa1Translate->addAttribute(new AttrVector3(vec3(0.0f, -90.0f, 0.0f), 20.4f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa1Translate->addAttribute(new AttrVector3(vec3(0.0f, -90.0f, 0.0f), 21.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa1Translate->addAttribute(new AttrVector3(vec3(0.0f, 90.0f, 0.0f), 21.8f, PoseAttr::ROTATE)); // tempo: 1 seg


	Interpolator * ptrInterpolatorLeftArm = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);
	Interpolator * ptrInterpolatorLeftForearm = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);
	Interpolator * ptrInterpolatorRightArm = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);
	Interpolator * ptrInterpolatorRightForearm = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);

	ptrInterpolatorLeftArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), 10, PoseAttr::ROTATE)); // tempo: 0 seg
	ptrInterpolatorLeftArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 120.0f), 11, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorLeftArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 95), 11.25, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorLeftArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 120.0f), 11.5, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorLeftArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 120.0f), 14, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorLeftArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), 15, PoseAttr::ROTATE)); // tempo: 1 seg

	ptrInterpolatorLeftForearm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), 7, PoseAttr::ROTATE)); // tempo: 0 seg
	ptrInterpolatorLeftForearm->addAttribute(new AttrVector3(vec3(90.0f, 0.0f, 0.0f), 8, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorLeftForearm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), 9, PoseAttr::ROTATE)); // tempo: 1 seg

	ptrInterpolatorRightArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), 10, PoseAttr::ROTATE)); // tempo: 0 seg
	ptrInterpolatorRightArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, -120.0f), 11, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorRightArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, -95.0f), 11.25, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorRightArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, -120.0f), 11.5, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorRightArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, -120.0f), 14, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorRightArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), 15, PoseAttr::ROTATE)); // tempo: 1 seg

	ptrInterpolatorRightForearm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), 9, PoseAttr::ROTATE)); // tempo: 0 seg
	ptrInterpolatorRightForearm->addAttribute(new AttrVector3(vec3(45.0f, 0.0f, 0.0f), 10, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorRightForearm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), 11, PoseAttr::ROTATE)); // tempo: 1 seg

	Animator* ptrPessoa1Animator = new Animator(Animator::ONCE);
	ptrPessoa1Animator->addInterpolator(ptrInterpolatorPessoa1Translate);

	Pessoa * ptrPessoa1 = new Pessoa();
	ptrPessoa1->ptrAnimatorLeftArm->addInterpolator(ptrInterpolatorLeftArm);
	ptrPessoa1->ptrAnimatorLeftForearm->addInterpolator(ptrInterpolatorLeftForearm);

	ptrPessoa1->ptrAnimatorRightArm->addInterpolator(ptrInterpolatorRightArm);
	ptrPessoa1->ptrAnimatorRightForearm->addInterpolator(ptrInterpolatorRightForearm);

	ptrPessoa1->addWalk(20, 21.5, 0.25);

	ptrPessoa1->Initialize();
	ptrPessoa1->setAnimator(ptrPessoa1Animator);
	ptrApp->AddEntity(ptrPessoa1);

	Interpolator * ptrInterpolatorPessoa2Translate = new PolinomialInterpolator(PolinomialInterpolator::Catmullrom);

	ptrInterpolatorPessoa2Translate->addAttribute(new AttrVector3(vec3(2.9f, 0.0f, -0.8f), 0.0f, PoseAttr::TRANSLATE)); // tempo: 0 seg
	ptrInterpolatorPessoa2Translate->addAttribute(new AttrVector3(vec3(2.9f, 0.0f, -0.8f), 20.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrInterpolatorPessoa2Translate->addAttribute(new AttrVector3(vec3(8.0f, 0.0f, -0.9f), 21.5f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrInterpolatorPessoa2Translate->addAttribute(new AttrVector3(vec3(0.0f, -45.0f, 0.0f), 0.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa2Translate->addAttribute(new AttrVector3(vec3(0.0f, -45.0f, 0.0f), 10.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa2Translate->addAttribute(new AttrVector3(vec3(0.0f, -60.0f, 0.0f), 11.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa2Translate->addAttribute(new AttrVector3(vec3(0.0f, -60.0f, 0.0f), 13.50f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa2Translate->addAttribute(new AttrVector3(vec3(0.0f, -45.0f, 0.0f), 14.0f, PoseAttr::ROTATE)); // tempo: 1 seg

	ptrInterpolatorPessoa2Translate->addAttribute(new AttrVector3(vec3(0.0f, -45.0f, 0.0f), 18.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa2Translate->addAttribute(new AttrVector3(vec3(0.0f, 75.0f, 0.0f), 18.4f, PoseAttr::ROTATE)); // tempo: 1 seg

	ptrInterpolatorPessoa2Translate->addAttribute(new AttrVector3(vec3(0.0f, 75.0f, 0.0f), 20.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa2Translate->addAttribute(new AttrVector3(vec3(0.0f, -90.0f, 0.0f), 20.4f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa2Translate->addAttribute(new AttrVector3(vec3(0.0f, -90.0f, 0.0f), 21.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa2Translate->addAttribute(new AttrVector3(vec3(0.0f, 90.0f, 0.0f), 22.3f, PoseAttr::ROTATE)); // tempo: 1 seg

	Animator* ptrPessoa2Animator = new Animator(Animator::ONCE);
	ptrPessoa2Animator->addInterpolator(ptrInterpolatorPessoa2Translate);

	Pessoa * ptrPessoa2 = new Pessoa();
	ptrPessoa2->addWalk(20, 21.5, 0.25);
	ptrPessoa2->Initialize();
	ptrPessoa2->setAnimator(ptrPessoa2Animator);
	ptrApp->AddEntity(ptrPessoa2);

	Interpolator * ptrInterpolatorPessoa3Translate = new PolinomialInterpolator(PolinomialInterpolator::Catmullrom);

	ptrInterpolatorPessoa3Translate->addAttribute(new AttrVector3(vec3(4.2f, 0.0f, -0.8f), 0.0f, PoseAttr::TRANSLATE)); // tempo: 0 seg
	ptrInterpolatorPessoa3Translate->addAttribute(new AttrVector3(vec3(4.2f, 0.0f, -0.8f), 20.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrInterpolatorPessoa3Translate->addAttribute(new AttrVector3(vec3(8.4f, 0.0f, -1.4f), 21.5f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrInterpolatorPessoa3Translate->addAttribute(new AttrVector3(vec3(0.0f, 40.0f, 0.0f), 0.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa3Translate->addAttribute(new AttrVector3(vec3(0.0f, 45.0f, 0.0f), 10.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa3Translate->addAttribute(new AttrVector3(vec3(0.0f, 60.0f, 0.0f), 11.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa3Translate->addAttribute(new AttrVector3(vec3(0.0f, 60.0f, 0.0f), 13.50f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa3Translate->addAttribute(new AttrVector3(vec3(0.0f, 45.0f, 0.0f), 14.0f, PoseAttr::ROTATE)); // tempo: 1 seg

	ptrInterpolatorPessoa3Translate->addAttribute(new AttrVector3(vec3(0.0f, 45.0f, 0.0f), 17.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa3Translate->addAttribute(new AttrVector3(vec3(0.0f, 75.0f, 0.0f), 17.4f, PoseAttr::ROTATE)); // tempo: 1 seg

	ptrInterpolatorPessoa3Translate->addAttribute(new AttrVector3(vec3(0.0f, 75.0f, 0.0f), 20.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa3Translate->addAttribute(new AttrVector3(vec3(0.0f, -90.0f, 0.0f), 20.4f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa3Translate->addAttribute(new AttrVector3(vec3(0.0f, -90.0f, 0.0f), 21.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorPessoa3Translate->addAttribute(new AttrVector3(vec3(0.0f, 90.0f, 0.0f), 22.0f, PoseAttr::ROTATE)); // tempo: 1 seg

	Animator* ptrPessoa3Animator = new Animator(Animator::ONCE);
	ptrPessoa3Animator->addInterpolator(ptrInterpolatorPessoa3Translate);

	Interpolator * ptrInterpolatorRightArmP3 = new PolinomialInterpolator(PolinomialInterpolator::Catmullrom);
	ptrInterpolatorRightArmP3->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), 17.7, PoseAttr::ROTATE)); // tempo: 0 seg
	ptrInterpolatorRightArmP3->addAttribute(new AttrVector3(vec3(95.0f, 0.0f, 0.0f), 18, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorRightArmP3->addAttribute(new AttrVector3(vec3(95.0f, 0.0f, 0.0f), 19, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorRightArmP3->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), 19.2, PoseAttr::ROTATE)); // tempo: 1 seg

	Pessoa * ptrPessoa3 = new Pessoa();

	ptrPessoa3->ptrAnimatorRightArm->addInterpolator(ptrInterpolatorRightArmP3);
	ptrPessoa3->addWalk(20, 21.5, 0.25);
	ptrPessoa3->Initialize();
	ptrPessoa3->setAnimator(ptrPessoa3Animator);
	ptrApp->AddEntity(ptrPessoa3);

	*/


	// **********************************************************
	//                            ACTOR: CARRO VRUM VRUM
	// **********************************************************
	/*
	Interpolator * ptrInterpolatorCarroTranslate = new LinearInterpolator();

	ptrInterpolatorCarroTranslate->addAttribute(new AttrVector3(vec3(-40.0f, 0.0f, -20.7f), 0.0f, PoseAttr::TRANSLATE)); // tempo: 0 seg
	ptrInterpolatorCarroTranslate->addAttribute(new AttrVector3(vec3(-40.0f, 0.0f, -2.7f), 14.0f, PoseAttr::TRANSLATE)); // tempo: 0 seg
	ptrInterpolatorCarroTranslate->addAttribute(new AttrVector3(vec3(-5.0f, 0.0f, -2.7f), 19.0f, PoseAttr::TRANSLATE)); // tempo: 0 seg
	ptrInterpolatorCarroTranslate->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, -2.7f), 20.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrInterpolatorCarroTranslate->addAttribute(new AttrVector3(vec3(3.0f, 1.0f, -2.7f), 20.5f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrInterpolatorCarroTranslate->addAttribute(new AttrVector3(vec3(5.0f, 0.8f, -2.7f), 21.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrInterpolatorCarroTranslate->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), 20.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorCarroTranslate->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, -180.0f), 21.0f, PoseAttr::ROTATE)); // tempo: 1 seg


	Animator *  ptrCarroAnimator = new Animator(Animator::ONCE);
	ptrCarroAnimator->addInterpolator(ptrInterpolatorCarroTranslate);

	Carro * ptrCarro = new Carro();
	ptrCarro->setAnimator(ptrCarroAnimator);
	ptrCarro->setScale(vec3(0.8, 0.8, 0.8));
	ptrApp->AddEntity(ptrCarro);
	*/
	// **********************************************************
	//                            ACTOR: PEAO
	// **********************************************************
	/*

	Interpolator * ptrPoliPeao = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);
	ptrPoliPeao->addAttribute(new AttrVector3(vec3(5.0f, 0.1f, -4.0f), 0.0f, PoseAttr::TRANSLATE)); // tempo: 0 seg
	ptrPoliPeao->addAttribute(new AttrVector3(vec3(0.0f, 0.1f, -4.0f), 10.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrPoliPeao->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), 10.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrPoliPeao->addAttribute(new AttrVector3(vec3(0.0f, 125.0f, 0.0f), 12.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrPoliPeao->addAttribute(new AttrVector3(vec3(0.0f, 125.0f, 0.0f), 13.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrPoliPeao->addAttribute(new AttrVector3(vec3(0.0f, 45.0f, 0.0f), 15.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrPoliPeao->addAttribute(new AttrVector3(vec3(0.0f, 45.0f, 0.0f), 16.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrPoliPeao->addAttribute(new AttrVector3(vec3(0.0f, 90.0f, 0.0f), 18.0f, PoseAttr::ROTATE)); // tempo: 1 seg

	Interpolator * ptrLinearPeao = new LinearInterpolator();
	ptrLinearPeao->addAttribute(new AttrVector3(vec3(0.0f, 0.1f, -4.0f), 18.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrLinearPeao->addAttribute(new AttrVector3(vec3(0.0f, 0.1f, -2.0f), 20.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg


	Animator *  ptrPeaoAnimator = new Animator(Animator::ONCE);
	ptrPeaoAnimator->addInterpolator(ptrPoliPeao);
	ptrPeaoAnimator->addInterpolator(ptrLinearPeao);
	//ptrPeaoAnimator->addInterpolator(ptrDesaceleraPeao);

	Peao* ptrPeao = new Peao();
	ptrPeao->setScale(vec3(0.3f, 0.3f, 0.3f));
	ptrPeao->setAnimator(ptrPeaoAnimator);

	ptrApp->AddEntity(ptrPeao);

	*/


	// **********************************************************
	//                            ACTOR: DAMAS
	// **********************************************************
	/*
	PolynomInterpolator * ptrInterpolatorDama = new PolynomInterpolator(PoseAttr::TRANSLATE);
	ptrInterpolatorDama->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, -10.0f), 0.0f, PoseAttr::TRANSLATE)); // tempo: 0 seg
	ptrInterpolatorDama->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, -10.0f), 22.0f, PoseAttr::TRANSLATE)); // tempo: 0 seg
	ptrInterpolatorDama->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, -3.0f), 25.0f, PoseAttr::TRANSLATE)); // tempo: 0 seg
	ptrInterpolatorDama->addAttribute(new AttrVector3(vec3(4.0f, 0.0f, -3.0f), 27.0f, PoseAttr::TRANSLATE)); // tempo: 0 seg


	ptrInterpolatorDama->Setup();

	Animator *  ptrDamaAnimator = new Animator(Animator::ONCE);
	ptrDamaAnimator->addInterpolator(ptrInterpolatorDama);

	Dama * ptrDama = new Dama();
	ptrDama->setScale(vec3(0.3f, 0.3f, 0.3f));
	ptrDama->setAnimator(ptrDamaAnimator);
	ptrApp->AddEntity(ptrDama);

	ptrApp->AddTimerFunction([ptrDama](double deltaTime) {
		ptrDama->setMass(10.0f);
		ptrDama->ActivatePhysics(Entity::BOX);

		ptrDama->getRigidBody()->setLinearVelocity(btVector3(-10, 1, 0));
		ptrDama->getRigidBody()->setAngularVelocity(btVector3(0, 0, 20));

	}, 30.0f);

	PolynomInterpolator * ptrInterpolatorDama2 = new PolynomInterpolator(PoseAttr::TRANSLATE);
	ptrInterpolatorDama2->addAttribute(new AttrVector3(vec3(0.5f, 0.0f, -10.0f), 0.0f, PoseAttr::TRANSLATE)); // tempo: 0 seg
	ptrInterpolatorDama2->addAttribute(new AttrVector3(vec3(0.5f, 0.0f, -10.0f), 22.0f, PoseAttr::TRANSLATE)); // tempo: 0 seg
	ptrInterpolatorDama2->addAttribute(new AttrVector3(vec3(0.5f, 0.0f, -3.0f), 25.0f, PoseAttr::TRANSLATE)); // tempo: 0 seg
	ptrInterpolatorDama2->addAttribute(new AttrVector3(vec3(4.3f, 0.0f, -3.5f), 27.0f, PoseAttr::TRANSLATE)); // tempo: 0 seg
																											  //ptrInterpolatorDama2->Setup();

	Interpolator * ptrJumpDama2 = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);
	ptrJumpDama2->addAttribute(new AttrVector3(vec3(4.3f, 0.0f, -3.5f), 28.0f, PoseAttr::TRANSLATE)); // tempo: 0 seg
	ptrJumpDama2->addAttribute(new AttrVector3(vec3(4.3f, 0.3f, -3.5f), 28.20f, PoseAttr::TRANSLATE)); // tempo: 0 seg
	ptrJumpDama2->addAttribute(new AttrVector3(vec3(4.3f, 0.0f, -3.5f), 28.40f, PoseAttr::TRANSLATE)); // tempo: 0 seg
	ptrJumpDama2->addAttribute(new AttrVector3(vec3(4.3f, 0.3f, -3.5f), 28.60f, PoseAttr::TRANSLATE)); // tempo: 0 seg
	ptrJumpDama2->addAttribute(new AttrVector3(vec3(4.3f, 0.0f, -3.5f), 28.80f, PoseAttr::TRANSLATE)); // tempo: 0 seg



	ptrInterpolatorDama2->Setup();
	Animator *  ptrDamaAnimator2 = new Animator(Animator::ONCE);
	ptrDamaAnimator2->addInterpolator(ptrInterpolatorDama2);
	ptrDamaAnimator2->addInterpolator(ptrJumpDama2);

	Dama * ptrDama2 = new Dama();
	ptrDama2->setScale(vec3(0.3f, 0.3f, 0.3f));
	ptrDama2->setAnimator(ptrDamaAnimator2);
	ptrApp->AddEntity(ptrDama2);

	ptrApp->AddTimerFunction([ptrDama2](double deltaTime) {
		ptrDama2->setMass(10.0f);
		ptrDama2->ActivatePhysics(Entity::BOX);

		ptrDama2->getRigidBody()->setLinearVelocity(btVector3(-20, 1, 0));

	}, 30.0f);

	*/
	// **********************************************************
	//                            ACTOR: VACA MU MU
	// **********************************************************
	/*
	Interpolator * ptrLinearTranslateVaca = new LinearInterpolator();
	ptrLinearTranslateVaca->addAttribute(new AttrVector3(vec3(1.0f, -0.1f, 2.5f), 0.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrLinearTranslateVaca->addAttribute(new AttrVector3(vec3(1.0f, -0.1f, 2.5f), 4.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrLinearTranslateVaca->addAttribute(new AttrVector3(vec3(5.0f, -0.1f, 2.5f), 15.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrLinearTranslateVaca->addAttribute(new AttrVector3(vec3(5.0f, -0.1f, 2.5f), 21.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrLinearTranslateVaca->addAttribute(new AttrVector3(vec3(5.0f, -0.1f, 9.0f), 25.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg

	Interpolator * ptrLinearRotateVaca = new LinearInterpolator();
	ptrLinearRotateVaca->addAttribute(new AttrVector3(vec3(0.0f, -90.0f, 0.0f), 19.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrLinearRotateVaca->addAttribute(new AttrVector3(vec3(0.0f, -180.0f, 0.0f), 20.0f, PoseAttr::ROTATE)); // tempo: 1 seg


	Animator *  ptrAniVaca = new Animator(Animator::ONCE);
	ptrAniVaca->addInterpolator(ptrLinearTranslateVaca);
	ptrAniVaca->addInterpolator(ptrLinearRotateVaca);

	Cow* vaca = new Cow();
	vaca->setRotate(vec3(0, -90, 0));
	vaca->addWalk(4, 15, 0.5);
	vaca->addWalk(19, 20, 0.5);
	vaca->addWalk(21, 25, 0.2);
	vaca->setAnimator(ptrAniVaca);
	vaca->Initialize();
	ptrApp->AddEntity(vaca);

	//  VACA 2 

	Interpolator * ptrLinearTranslateVaca2 = new LinearInterpolator();
	ptrLinearTranslateVaca2->addAttribute(new AttrVector3(vec3(8.0f, -0.1f, -5.5f), 0.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrLinearTranslateVaca2->addAttribute(new AttrVector3(vec3(8.0f, -0.1f, -5.5f), 2.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrLinearTranslateVaca2->addAttribute(new AttrVector3(vec3(12.0f, -0.1f, -5.5f), 6.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg

	Interpolator * ptrLinearRotateVaca2 = new LinearInterpolator();
	ptrLinearRotateVaca2->addAttribute(new AttrVector3(vec3(0.0f, -90.0f, 0.0f), 19.0f, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrLinearRotateVaca2->addAttribute(new AttrVector3(vec3(0.0f, -180.0f, 0.0f), 20.0f, PoseAttr::ROTATE)); // tempo: 1 seg


	Animator *  ptrAniVaca2 = new Animator(Animator::ONCE);
	ptrAniVaca2->addInterpolator(ptrLinearTranslateVaca2);
	ptrAniVaca2->addInterpolator(ptrLinearRotateVaca2);

	Cow* vaca2 = new Cow();
	vaca2->setRotate(vec3(0, -90, 0));
	vaca2->addWalk(2, 6, 0.5);
	vaca2->setAnimator(ptrAniVaca2);
	vaca2->Initialize();
	ptrApp->AddEntity(vaca2);
	*/

	// **********************************************************
	//                            ACTOR: CAMERA
	// **********************************************************
	Interpolator * ptrLinearCamera = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);
	ptrLinearCamera->addAttribute(new AttrVector3(vec3(3.0f, 1.0f, -4.0f), 0.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrLinearCamera->addAttribute(new AttrVector3(vec3(1.0f, 1.0f, -5.0f), 4.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrLinearCamera->addAttribute(new AttrVector3(vec3(1.0f, 1.0f, -5.0f), 6.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrLinearCamera->addAttribute(new AttrVector3(vec3(-2.0f, 1.0f, -5.0f), 11.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrLinearCamera->addAttribute(new AttrVector3(vec3(-2.0f, 1.0f, -5.0f), 20.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrLinearCamera->addAttribute(new AttrVector3(vec3(0.0f, 1.0f, -5.0f), 23.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg

	ptrLinearCamera->addAttribute(new AttrVector3(vec3(0.0f, 1.0f, -5.0f), 29.8f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrLinearCamera->addAttribute(new AttrVector3(vec3(0.0f, 1.1f, -5.1f), 29.9f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrLinearCamera->addAttribute(new AttrVector3(vec3(0.0f, 0.9f, -4.9f), 30.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
	ptrLinearCamera->addAttribute(new AttrVector3(vec3(0.0f, 1.0f, -5.0f), 30.1f, PoseAttr::TRANSLATE)); // tempo: 1 seg

	Animator *  ptrCameraAnim = new Animator(Animator::ONCE);
	ptrCameraAnim->addInterpolator(ptrLinearCamera);

	Camera* cam = new Camera();
	cam->setTranslate(vec3(0, 2, -5));
	//cam->setAnimator(ptrCameraAnim);

	ptrApp->AddEntity(cam);


	// **********************************************************
	//                            ACTOR: LIGHT
	// **********************************************************

	Interpolator * ptrLinearLight = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);
	ptrLinearLight->addAttribute(new AttrVector3(vec3(10, 3, -20), 0.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg

	Animator *  ptrLightAnim = new Animator(Animator::ONCE);
	ptrLightAnim->addInterpolator(ptrLinearLight);

	vec3 lightPos = vec3(-10, 4, -10);
	Light* light = new Light();
	//light->setAnimator(ptrLightAnim);
	light->setTranslate(lightPos);
	ptrApp->AddEntity(light);



	//ptrApp->ptrv3CameraPos = new vec3(2, 1, -5);


	// **********************************************************
	//                            PHYSICS: BOLA
	// **********************************************************
	vec3 posAtt(0.0f, 5.0f, 0.0f);
	vec3 posAtt1(3.0f, 7.0f, 0.0f);
	vec3 posAtt2(-3.0f, 6.0f, 0.0f);


	Model* ptrBallP = new Model("objs/box.obj", "textures/azul_c.jpg");
	ptrBallP->setScale(vec3(0.2f, 0.2f, 0.2f));
	ptrBallP->setTranslate(vec3(3.0f, 10.0f, 0.0f));
	ptrBallP->setMass(1);
	//ptrBallP->LoadDimensions();
	ptrBallP->ActivatePhysics(Entity::BOX);


	//ptrBallP->setRigidBody(ptrRigidBall);

	//ptrRigidBall->setBoundingAABB();

	ptrApp->AddEntity(ptrBallP);

	//ptrBallP = new Model("objs/circle.obj", "textures/vermelho.jpg");
	//ptrBallP->setScale(vec3(0.2f, 0.2f, 0.2f));
	//ptrBallP->setTranslate(posAtt);

	//ptrApp->AddEntity(ptrBallP);


	// **********************************************************
	//                            PHYSICS: CLOTH
	// **********************************************************
	Cloth* cloth = new Cloth(1, 1, 40, 40);
	cloth->SetGravity(vec3(0, -0.01, 0));
	cloth->SetWind(vec3(2.5, 0, 0));
	cloth->setTranslate(vec3(0.1, 0.4, 0.4));
	cloth->WindForce(vec3(20, 0, 0), 20.0f);

	cloth->WindForce(vec3(-20, 0, -5), 5.0f);

	ptrApp->AddEntity(cloth);

	// **********************************************************
	//                            TESTING AREA
	// **********************************************************
	for (int i = 64; i >= 0; --i)
	{
		for (int j = 128; j >= 0; --j) {
			BillBoard *bp = new BillBoard("textures/grass.png");
			float s = Utilities::map(rand() % 1000, 0, 1000, 0.4, 0.7);
			float dX = (rand() % 2) * 0.6f - 0.3f;
			float dZ = (rand() % 2) * 0.6f - 0.3f;
			bp->setTranslate(vec3(j / 2.0f - 32.0f + dX, s / 2.0f, i / 2.0f + dZ));
			bp->SetSize(vec2(s, s));
			bp->SetShearable(true);
			ptrApp->AddBillboard(bp);
		}
	}
	for (int i = 16; i >= 0; --i)
	{
		Cloud *bp = new Cloud(rand() % 3 < 1 ? "textures/cloud.png" : "textures/cloud2.png");
		float x = rand() % 32 - 16.0f;
		float xDest = min(x - rand() % 32, x - 10.0f);
		float y = rand() % 3 + 7.0f;
		float z = 10 + i * 2.0f;
		float sX = rand() % 5 + 1.0f;


		Interpolator * ptrCloudInter = new LinearInterpolator();
		ptrCloudInter->addAttribute(new AttrVector3(vec3(x, y, z), 0.0f, PoseAttr::TRANSLATE)); // tempo: 1 seg
		ptrCloudInter->addAttribute(new AttrVector3(vec3(xDest, y, z), 40, PoseAttr::TRANSLATE)); // tempo: 1 seg


		Animator *  ptrCloudAni = new Animator(Animator::ONCE);
		ptrCloudAni->addInterpolator(ptrCloudInter);

		bp->setTranslate(vec3(x, y, z));
		bp->setSize(vec2(sX, sX));
		bp->setAnimator(ptrCloudAni);
		ptrApp->AddBillboard(bp);

	}

	// **********************************************************
	//                            EXPLOSION
	// **********************************************************
	/*

	ptrApp->AddTimerFunction([ptrCarro](double dDeltaTime) {

		for (int i = 0; i < ptrApp->getEntityCount(); ++i)
		{
			Entity* ent = ptrApp->GetEntity(i);
			if (ent->hasRigidBody()) {
				float dif = -10.0f;
				vec3 dist = (ptrCarro->getTranslate() - ent->getTranslate());
				ent->getRigidBody()->setLinearVelocity(btVector3(dif / dist.x, dif / dist.y, dif / dist.z));
			}
		}

		ParticleSystem* psRodaTraseira = new ParticleSystem("textures/cloud2.png", 5000, vec3(5.0f, 0.2f, -2.7f));
		ptrApp->AddParticleSystem(psRodaTraseira);

		psRodaTraseira->SetBirthFunction([](double dDeltaTime, ParticleSystem::Particle* p, ParticleSystem* ps) {
			p->fLife = 2.f;
			p->fTotalLife = p->fLife;
			p->vPosition = ps->GetEmitter()->GetWorldPosition();
			float spread;
			if (ptrApp->GetApplicationTime() < 30.5)
				spread = 1.5f;
			else
				spread = 0.5;
			glm::vec3 randomdir = glm::vec3(
				(rand() % 2000 - 1000.0f) / 1000.0f,
				(rand() % 2000 - 1000.0f) / 1000.0f,
				(rand() % 2000 - 1000.0f) / 1000.0f
			);
			p->vSpeed = randomdir*spread;

			p->cR = 255;
			p->cG = 50;
			p->cB = 0;

			p->cA = 100;

			p->fSize = 0.5f;
		});

		psRodaTraseira->SetOnLoopFunction([](double dDeltaTime, ParticleSystem::Particle* p, ParticleSystem* ps) {
			p->vSpeed += glm::vec3(0.f, 2.f, 0.0f) * (float)(dDeltaTime * 0.5f);
			p->vPosition += p->vSpeed * (float)dDeltaTime;

			p->cG = Utilities::map(p->fLife, p->fTotalLife, 0.0f, 0.0f, 255.0f);

			p->cA = Utilities::map(p->fLife, p->fTotalLife, 0.0f, 100.0f, 0.0f);

			p->fSize = Utilities::map(p->fLife, p->fTotalLife, 0.0f, 0.001f, 0.55f);

		});

		psRodaTraseira->SetDeathFunction([](double dDeltaTime, ParticleSystem::Particle *par, ParticleSystem* ps) {
			if (rand() % 50 < 5 && ptrApp->GetApplicationTime() < 35) {
				ParticleSystem* psRodaTraseira = new ParticleSystem("textures/cloud2.png", 1, vec3(5.0f, 0.2f, -2.7f));
				ptrApp->AddParticleSystem(psRodaTraseira);

				psRodaTraseira->SetBirthFunction([par](double dDeltaTime, ParticleSystem::Particle* p, ParticleSystem* ps) {
					p->fLife = 5.f;
					p->fTotalLife = p->fLife;
					p->vPosition = par->vPosition;
					float spread;
					if (ptrApp->GetApplicationTime() < 30.5)
						spread = 1.5f;
					else
						spread = 0.5;
					glm::vec3 randomdir = glm::vec3(
						(rand() % 2000 - 1000.0f) / 1000.0f,
						(rand() % 2000 - 1000.0f) / 1000.0f,
						(rand() % 2000 - 1000.0f) / 1000.0f
					);
					p->vSpeed = randomdir*spread;

					p->cR = 100;
					p->cG = 100;
					p->cB = 100;

					p->cA = 100;

					p->fSize = 0.5f;

					ps->SetBirthFunction([](double dDeltaTime, ParticleSystem::Particle* p, ParticleSystem* ps) {
						return;
					});
				});

				psRodaTraseira->SetOnLoopFunction([](double dDeltaTime, ParticleSystem::Particle* p, ParticleSystem* ps) {
					p->vSpeed += glm::vec3(0.f, -1.f, 0.0f) * (float)(dDeltaTime * 0.5f);
					p->vPosition += p->vSpeed * (float)dDeltaTime;

					if (p->vPosition.y < 0.0f) {
						p->vSpeed.y *= -1.0f;
						p->vPosition.y = 0;
					}
					
					p->cA = Utilities::map(p->fLife, p->fTotalLife, 0.0f, 100.0f, 0.0f);

					p->fSize = Utilities::map(p->fLife, p->fTotalLife, 0.0f, 0.001f, 0.55f);

				});

				psRodaTraseira->SetDeathFunction([](double dDeltaTime, ParticleSystem::Particle *p, ParticleSystem* ps) {
					p->fCameraDist = -1.0f;
					ps->SetOnLoopFunction([](double dDeltaTime, ParticleSystem::Particle* p, ParticleSystem* ps) {
						return;
					});

				});

			}
			par->fCameraDist = -1.0f;
		});

	}, 29.5);

	*/

	// **********************************************************
	//                            DIEL PRODUCOES
	// **********************************************************
	Model *prod = new Model("objs/prod.obj", "textures/branco.jpg");
	prod->setTranslate(vec3(10, 100, -2));
	prod->setRotate(vec3(0, -90, 0));
	ptrApp->AddEntity(prod);

	prod->setMass(15.0f);
	prod->ActivatePhysics(Entity::BOX);

	for (auto letra : { 3,2,1,0 }) {
		char * nome;
		switch (letra)
		{
		case 0:
			nome = "objs/D.obj";
			break;
		case 1:
			nome = "objs/i.obj";
			break;
		case 2:
			nome = "objs/e.obj";
			break;
		case 3:
			nome = "objs/L.obj";
			break;
		default:
			nome = "objs/circle1cm.obj";
			break;
		}

		Model *cubo = new Model(nome, "textures/branco.jpg");
		cubo->setTranslate(vec3(10, 0.8, -10 + letra));
		cubo->setRotate(vec3(0, -90, 0));
		ptrApp->AddEntity(cubo);



		ptrApp->AddTimerFunction([cubo](double dDeltaTime) {
			cubo->setMass(18.0f);
			cubo->ActivatePhysics(Entity::BOX);
			cubo->getRigidBody()->setLinearVelocity(btVector3(0, 0, 12));
		}, 2.0f);
		
	}

	// 1
	Pessoa *cubo;
	for (int letra = 0; letra < 2; letra++) {
		cubo = new Pessoa();
		cubo->setTranslate(vec3(letra, 0, 0));
		cubo->addWalk(0, 100, 0.25);
		cubo->Initialize();
		ptrApp->AddEntity(cubo);

		Vehicle* veh = new Vehicle(cubo);
		//veh->AddBehaviour(new SeekBehaviour(cam));
		//veh->AddBehaviour(new AvoidBoidBehaviour());

		veh->AddBehaviour(new AvoidObstacleBehaviour(arvores));
		veh->AddBehaviour(new WanderBehaviour());
		veh->AddBehaviour(new StayWithin());


		for (int letra = 0; letra < 5; letra++) {
			Cow *cuboF = new Cow();
			cuboF->setTranslate(vec3(letra, 0, 8));
			cuboF->addWalk(0, 100, 0.5);
			cuboF->Initialize();
			ptrApp->AddEntity(cuboF);

			Vehicle* veh = new Vehicle(cuboF);
			veh->AddBehaviour(new SeekBehaviour(cubo));
			veh->AddBehaviour(new AvoidBoidBehaviour());
			veh->AddBehaviour(new AvoidObstacleBehaviour(arvores));
			veh->AddBehaviour(new StayWithin());

		}

	}


	for (int letra = 0; letra < 20; letra++) {
		Cow *cuboF = new Cow();
		cuboF->setTranslate(vec3(letra, 0, 8));
		cuboF->setScale(vec3(0.75, 0.75, 0.75));
		cuboF->addWalk(0, 100, 1.0);
		cuboF->Initialize();
		ptrApp->AddEntity(cuboF);

		Vehicle* veh = new Vehicle(cuboF);
		veh->AddBehaviour(new AvoidBoidBehaviour());
		veh->AddBehaviour(new AvoidObstacleBehaviour(arvores));
		veh->AddBehaviour(new WanderBehaviour());
		veh->AddBehaviour(new StayWithin());

		veh->SetMaxSpeed(0.005);

	}

	for (int letra = 0; letra < 20; letra++) {
		Dove *cuboF = new Dove();
		cuboF->setTranslate(vec3(letra, 4, 8));		
		cuboF->Initialize();
		ptrApp->AddEntity(cuboF);

		Vehicle* veh = new Vehicle(cuboF);
		veh->AddBehaviour(new AvoidBoidBehaviour());
		veh->AddBehaviour(new AvoidObstacleBehaviour(arvores));
		veh->AddBehaviour(new WanderBehaviour());
		veh->AddBehaviour(new StayWithin());

		veh->SetMaxSpeed(0.05);

	}
	
	// **********************************************************
	//                            END SCENE
	// **********************************************************

	ptrApp->ptrlMainLight = light;
	ptrApp->ptrcMainCamera = cam;
	ptrApp->ptraCameraTarget = cubo;//ptrPeao->getBase();

	ptrApp->InitApplication(); 

	printf("%d particulas\n", ptrApp->iParticleCount);
	int a;
	//scanf("%d", &a);
	return 0;
}



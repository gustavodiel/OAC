#include "stdafx.h"
#include "Cow.h"

#include "Model.h"
#include "BodyMember.h"

#include "AttrVector3.h"
#include "Interpolator.h"
#include "PoseAttr.h"
#include "PolinomialInterpolator.hpp"
#include "LinearInterpolator.h"
#include "BlockingInterpolator.hpp"
#include "Animator.h"


Cow::Cow()
{
	this->ptrAnimatorFrontLeftLeg = new Animator(Animator::ONCE);
	this->ptrAnimatorFrontRightLeg = new Animator(Animator::ONCE);
	this->ptrAnimatorBackLeftLeg = new Animator(Animator::ONCE);
	this->ptrAnimatorBackRightLeg = new Animator(Animator::ONCE);
/*
	this->ptrAnimatorSelf = new Animator(Animator::ONCE);*/
}


Cow::~Cow()
{
}

void Cow::addWalk(double start, double finish, double step = 1.0) {

	Interpolator * ptrInterpolatorLeftArm = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);
	Interpolator * ptrInterpolatorRightArm = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);
	Interpolator * ptrInterpolatorLeftLeg = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);
	Interpolator * ptrInterpolatorRightLeg = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);
/*
	Interpolator * ptrInterpolatorSelf = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);*/

	ptrInterpolatorLeftArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), start, PoseAttr::ROTATE)); // tempo: 0 seg
	ptrInterpolatorRightArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), start, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorLeftLeg->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), start, PoseAttr::ROTATE)); // tempo: 0 seg
	ptrInterpolatorRightLeg->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), start, PoseAttr::ROTATE)); // tempo: 0 seg

	double i;
	for (i = start; i < finish; i += step * 2) {
		ptrInterpolatorLeftArm->addAttribute(new AttrVector3(vec3(45.0f, 0.0f, 0.0f), i, PoseAttr::ROTATE)); // tempo: 1 seg
		ptrInterpolatorLeftArm->addAttribute(new AttrVector3(vec3(-45.0f, 0.0f, 0.0f), i + step, PoseAttr::ROTATE)); // tempo: 1 seg

		ptrInterpolatorRightArm->addAttribute(new AttrVector3(vec3(-45.0f, 0.0f, 0.0f), i, PoseAttr::ROTATE)); // tempo: 1 seg
		ptrInterpolatorRightArm->addAttribute(new AttrVector3(vec3(45.0f, 0.0f, 0.0f), i + step, PoseAttr::ROTATE)); // tempo: 1 seg

		ptrInterpolatorLeftLeg->addAttribute(new AttrVector3(vec3(-45.0f, 0.0f, 0.0f), i, PoseAttr::ROTATE)); // tempo: 1 seg
		ptrInterpolatorLeftLeg->addAttribute(new AttrVector3(vec3(45.0f, 0.0f, 0.0f), i + step, PoseAttr::ROTATE)); // tempo: 1 seg

		ptrInterpolatorRightLeg->addAttribute(new AttrVector3(vec3(45.0f, 0.0f, 0.0f), i, PoseAttr::ROTATE)); // tempo: 1 seg
		ptrInterpolatorRightLeg->addAttribute(new AttrVector3(vec3(-45.0f, 0.0f, 0.0f), i + step, PoseAttr::ROTATE)); // tempo: 1 seg

	}



	ptrInterpolatorLeftArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), finish + step, PoseAttr::ROTATE)); // tempo: 0 seg
	ptrInterpolatorRightArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), finish + step, PoseAttr::ROTATE)); // tempo: 1 seg
	ptrInterpolatorLeftLeg->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), finish + step, PoseAttr::ROTATE)); // tempo: 0 seg
	ptrInterpolatorRightLeg->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), finish + step, PoseAttr::ROTATE)); // tempo: 0 seg

	this->ptrAnimatorFrontLeftLeg->addInterpolator(ptrInterpolatorLeftArm);
	this->ptrAnimatorFrontRightLeg->addInterpolator(ptrInterpolatorRightArm);
	this->ptrAnimatorBackLeftLeg->addInterpolator(ptrInterpolatorLeftLeg);
	this->ptrAnimatorBackRightLeg->addInterpolator(ptrInterpolatorRightLeg);
/*
	this->ptrAnimatorSelf->addInterpolator(ptrInterpolatorSelf);*/

}


void Cow::Initialize() {
	/* Corpo */
	Model* corpo = new Model("objs/box.obj", "textures/branco.jpg");
	corpo->setScale(glm::vec3(0.25, 0.25, 0.5));
	corpo->setTranslate(glm::vec3(0, 0.5, 0));
	this->listOfEntities.push_back(corpo);

	Model* head = new Model("objs/box.obj", "textures/preto.jpg");
	head->setScale(glm::vec3(0.2, 0.2, 0.1));
	head->setTranslate(glm::vec3(0, 0.65, -0.25));
	this->listOfEntities.push_back(head);

	/* Pata Frente esquerda */
	Model* leftArmJoint = new Model("objs/circle.obj", "textures/branco.jpg");
	leftArmJoint->setScale(glm::vec3(0.03, 0.03, 0.03));
	leftArmJoint->setTranslate(glm::vec3(0.1, 0.4, -0.2));
	this->listOfEntities.push_back(leftArmJoint);

	this->frontLeftLeg = new BodyMember("textures/preto.jpg");
	this->frontLeftLeg->setTranslate(glm::vec3(0.1, 0, -0.15));
	this->frontLeftLeg->setScale(glm::vec3(0.07, 0.3, 0.07));
	this->frontLeftLeg->setPivot(glm::vec3(0, 0.4, -0.05));
	this->listOfJoints.push_back(this->frontLeftLeg);

	/* Pata Frente direita */
	Model* rightArmJoint = new Model("objs/circle.obj", "textures/branco.jpg");
	rightArmJoint->setScale(glm::vec3(0.03, 0.03, 0.03));
	rightArmJoint->setTranslate(glm::vec3(-0.1, 0.4, -0.2));
	this->listOfEntities.push_back(rightArmJoint);

	this->frontRightLeg = new BodyMember("textures/preto.jpg");
	this->frontRightLeg->setTranslate(glm::vec3(-0.1, 0, -0.15));
	this->frontRightLeg->setScale(glm::vec3(0.07, 0.3, 0.07));
	this->frontRightLeg->setPivot(glm::vec3(0, 0.4, -0.05));
	this->listOfJoints.push_back(this->frontRightLeg);

	/* Pata Traseira direita */
	Model* rightLegJoint = new Model("objs/circle.obj", "textures/branco.jpg");
	rightLegJoint->setScale(glm::vec3(0.03, 0.03, 0.03));
	rightLegJoint->setTranslate(glm::vec3(-0.1, 0.4, 0.2));
	this->listOfEntities.push_back(rightLegJoint);

	this->backRightLeg = new BodyMember("textures/preto.jpg");
	this->backRightLeg->setTranslate(glm::vec3(-0.1, 0, 0.25));
	this->backRightLeg->setScale(glm::vec3(0.07, 0.3, 0.07));
	this->backRightLeg->setPivot(glm::vec3(0, 0.4, -0.05));
	this->listOfJoints.push_back(this->backRightLeg);

	/* Pata Traseira esquerda */
	Model* leftLegJoint = new Model("objs/circle.obj", "textures/branco.jpg");
	leftLegJoint->setScale(glm::vec3(0.03, 0.03, 0.03));
	leftLegJoint->setTranslate(glm::vec3(0.1, 0.4, 0.2));
	this->listOfEntities.push_back(leftLegJoint);

	this->backLeftLeg = new BodyMember("textures/preto.jpg");
	this->backLeftLeg->setTranslate(glm::vec3(0.1, 0, 0.25));
	this->backLeftLeg->setScale(glm::vec3(0.07, 0.3, 0.07));
	this->backLeftLeg->setPivot(glm::vec3(0, 0.4, -0.05));
	this->listOfJoints.push_back(this->backLeftLeg);

	/* Initilize the Animators */

	this->frontLeftLeg->setAnimator(this->ptrAnimatorFrontLeftLeg);
	this->frontRightLeg->setAnimator(this->ptrAnimatorFrontRightLeg);

	this->backRightLeg->setAnimator(this->ptrAnimatorBackRightLeg);
	this->backLeftLeg->setAnimator(this->ptrAnimatorBackLeftLeg);

	this->setAnimator(this->ptrAnimatorSelf);

}
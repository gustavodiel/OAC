#include "stdafx.h"
#include "Pessoa.h"

#include "Model.h"
#include "BodyMember.h"

#include "AttrVector3.h"
#include "Interpolator.h"
#include "PoseAttr.h"
#include "PolinomialInterpolator.hpp"
#include "LinearInterpolator.h"
#include "BlockingInterpolator.hpp"
#include "Animator.h"


Pessoa::Pessoa()
{
	this->ptrAnimatorLeftArm = new Animator(Animator::ONCE);
	this->ptrAnimatorLeftForearm = new Animator(Animator::ONCE);
	this->ptrAnimatorRightArm = new Animator(Animator::ONCE);
	this->ptrAnimatorRightForearm = new Animator(Animator::ONCE);
	this->ptrAnimatorLeftLeg = new Animator(Animator::ONCE);
	this->ptrAnimatorRighLeg = new Animator(Animator::ONCE);
}


Pessoa::~Pessoa()
{
}

void Pessoa::addWalk(double start, double finish, double step = 1.0) {

	Interpolator * ptrInterpolatorLeftArm = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);
	Interpolator * ptrInterpolatorLeftForearm = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);
	Interpolator * ptrInterpolatorRightArm = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);
	Interpolator * ptrInterpolatorRightForearm = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);
	Interpolator * ptrInterpolatorLeftLeg = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);
	Interpolator * ptrInterpolatorRightLeg = new PolinomialInterpolator(PolinomialInterpolator::CubicaEQuadrada);

	

	for (double i = start; i < finish; i += step * 2) {
		ptrInterpolatorLeftArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), i, PoseAttr::ROTATE)); // tempo: 0 seg
		ptrInterpolatorLeftArm->addAttribute(new AttrVector3(vec3(90.0f, 0.0f, 0.0f), i + step, PoseAttr::ROTATE)); // tempo: 1 seg
		ptrInterpolatorLeftArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), i + step * 2.0, PoseAttr::ROTATE)); // tempo: 1 seg

		ptrInterpolatorLeftForearm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), i, PoseAttr::ROTATE)); // tempo: 0 seg
		ptrInterpolatorLeftForearm->addAttribute(new AttrVector3(vec3(90.0f, 0.0f, 0.0f), i + step, PoseAttr::ROTATE)); // tempo: 1 seg
		ptrInterpolatorLeftForearm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), i + step * 2.0, PoseAttr::ROTATE)); // tempo: 1 seg

		ptrInterpolatorRightArm->addAttribute(new AttrVector3(vec3(90.0f, 0.0f, 0.0f), i, PoseAttr::ROTATE)); // tempo: 0 seg
		ptrInterpolatorRightArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), i + step, PoseAttr::ROTATE)); // tempo: 1 seg
		ptrInterpolatorRightArm->addAttribute(new AttrVector3(vec3(90.0f, 0.0f, 0.0f), i + step * 2.0, PoseAttr::ROTATE)); // tempo: 1 seg

		ptrInterpolatorRightForearm->addAttribute(new AttrVector3(vec3(90.0f, 0.0f, 0.0f), i, PoseAttr::ROTATE)); // tempo: 0 seg
		ptrInterpolatorRightForearm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), i + step, PoseAttr::ROTATE)); // tempo: 1 seg
		ptrInterpolatorRightForearm->addAttribute(new AttrVector3(vec3(90.0f, 0.0f, 0.0f), i + step * 2.0, PoseAttr::ROTATE)); // tempo: 1 seg

		ptrInterpolatorLeftLeg->addAttribute(new AttrVector3(vec3(90.0f, 0.0f, 0.0f), i, PoseAttr::ROTATE)); // tempo: 0 seg
		ptrInterpolatorLeftLeg->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), i + step, PoseAttr::ROTATE)); // tempo: 1 seg
		ptrInterpolatorLeftLeg->addAttribute(new AttrVector3(vec3(90.0f, 0.0f, 0.0f), i + step * 2.0, PoseAttr::ROTATE)); // tempo: 1 seg

		ptrInterpolatorRightLeg->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), i, PoseAttr::ROTATE)); // tempo: 0 seg
		ptrInterpolatorRightLeg->addAttribute(new AttrVector3(vec3(90.0f, 0.0f, 0.0f), i + step, PoseAttr::ROTATE)); // tempo: 1 seg
		ptrInterpolatorRightLeg->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), i + step * 2.0, PoseAttr::ROTATE)); // tempo: 1 seg

	}

	ptrInterpolatorLeftArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), finish + step, PoseAttr::ROTATE)); // tempo: 0 seg
	ptrInterpolatorLeftForearm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), finish + step, PoseAttr::ROTATE)); // tempo: 1 seg

	ptrInterpolatorRightArm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), finish + step, PoseAttr::ROTATE)); // tempo: 0 seg
	ptrInterpolatorRightForearm->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), finish + step, PoseAttr::ROTATE)); // tempo: 1 seg

	ptrInterpolatorLeftLeg->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), finish + step, PoseAttr::ROTATE)); // tempo: 0 seg
	ptrInterpolatorRightLeg->addAttribute(new AttrVector3(vec3(0.0f, 0.0f, 0.0f), finish + step, PoseAttr::ROTATE)); // tempo: 0 seg

	ptrAnimatorLeftArm->addInterpolator(ptrInterpolatorLeftArm);
	ptrAnimatorLeftForearm->addInterpolator(ptrInterpolatorLeftForearm);

	ptrAnimatorRightArm->addInterpolator(ptrInterpolatorRightArm);
	ptrAnimatorRightForearm->addInterpolator(ptrInterpolatorRightForearm);

	ptrAnimatorLeftLeg->addInterpolator(ptrInterpolatorLeftLeg);
	ptrAnimatorRighLeg->addInterpolator(ptrInterpolatorRightLeg);
	
}

void Pessoa::Initialize() {
	/* Corpo */
	Model* corpo = new Model("objs/box.obj", "textures/vermelho.jpg");
	corpo->setScale(glm::vec3(0.3, 0.4, 0.1));
	corpo->setTranslate(glm::vec3(0, 0.6, 0));
	this->listOfEntities.push_back(corpo);

	Model* head = new Model("objs/box.obj", "textures/azul_c.jpg");
	head->setScale(glm::vec3(0.2, 0.2, 0.1));
	head->setTranslate(glm::vec3(0, 0.9, 0));
	this->listOfEntities.push_back(head);

	/* Braco esquerdo */
	Model* leftArmJoint = new Model("objs/circle.obj", "textures/vermelho.jpg");
	leftArmJoint->setScale(glm::vec3(0.03, 0.03, 0.03));
	leftArmJoint->setTranslate(glm::vec3(0.2, 0.7, 0));
	this->listOfEntities.push_back(leftArmJoint);

	this->leftArm = new BodyMember("textures/branco.jpg");
	this->leftArm->setTranslate(glm::vec3(0.2, 0.3, 0.05));
	this->leftArm->setScale(glm::vec3(0.07, 0.15, 0.07));
	this->leftArm->setPivot(glm::vec3(0, 0.4, -0.05));
	this->listOfJoints.push_back(this->leftArm);

	this->leftForearm = new BodyMember("textures/branco.jpg");
	this->leftForearm->setScale(glm::vec3(0.07, 0.15, 0.07));
	this->leftForearm->setTranslate(glm::vec3(0, -0.63, 0.47));
	this->leftForearm->setPivot(glm::vec3(0, 0.5, -0.5));
	this->leftArm->Attach(this->leftForearm);

	/* Braco direito */
	Model* rightArmJoint = new Model("objs/circle.obj", "textures/vermelho.jpg");
	rightArmJoint->setScale(glm::vec3(0.03, 0.03, 0.03));
	rightArmJoint->setTranslate(glm::vec3(-0.2, 0.7, 0));
	this->listOfEntities.push_back(rightArmJoint);

	this->rightArm = new BodyMember("textures/branco.jpg");
	this->rightArm->setTranslate(glm::vec3(-0.2, 0.3, 0.05));
	this->rightArm->setScale(glm::vec3(0.07, 0.15, 0.07));
	this->rightArm->setPivot(glm::vec3(0, 0.4, -0.05));
	this->listOfJoints.push_back(this->rightArm);

	this->rightForearm = new BodyMember("textures/branco.jpg");
	this->rightForearm->setScale(glm::vec3(0.07, 0.15, 0.07));
	this->rightForearm->setTranslate(glm::vec3(0, -0.63, 0.47));
	this->rightForearm->setPivot(glm::vec3(0, 0.5, -0.5));
	this->rightArm->Attach(this->rightForearm);

	/* Perna direita */
	Model* rightLegJoint = new Model("objs/circle.obj", "textures/vermelho.jpg");
	rightLegJoint->setScale(glm::vec3(0.025, 0.025, 0.025));
	rightLegJoint->setTranslate(glm::vec3(-0.1, 0.4, 0));
	this->listOfEntities.push_back(rightLegJoint);

	this->rightLeg = new BodyMember("textures/branco.jpg");
	this->rightLeg->setTranslate(glm::vec3(-0.1, 0.0, 0.05));
	this->rightLeg->setScale(glm::vec3(0.07, 0.3, 0.07));
	this->rightLeg->setPivot(glm::vec3(0, 0.4, -0.05));
	this->listOfJoints.push_back(this->rightLeg);

	/* Perna esquerda */
	Model* leftLegJoint = new Model("objs/circle.obj", "textures/vermelho.jpg");
	leftLegJoint->setScale(glm::vec3(0.025, 0.025, 0.025));
	leftLegJoint->setTranslate(glm::vec3(0.1, 0.4, 0));
	this->listOfEntities.push_back(leftLegJoint);

	this->leftLeg = new BodyMember("textures/branco.jpg");
	this->leftLeg->setTranslate(glm::vec3(0.1, 0.0, 0.05));
	this->leftLeg->setScale(glm::vec3(0.07, 0.3, 0.07));
	this->leftLeg->setPivot(glm::vec3(0, 0.4, -0.05));
	this->listOfJoints.push_back(this->leftLeg);

	//this->LoadDimensions();

	//vec3 peaoMax = this->GetMaxValue();
	//vec3 peaoMin = this->GetMinValue();
	//vec3 cubo1Pos = this->GetCenter();

	//Model *cubo1 = new Model("objs/box.obj", "textures/vermelho.jpg");
	//cubo1->setScale(vec3(1, 0.1, 1));
	//cubo1->setTranslate(cubo1Pos);
	//cubo1->SetWireframe(true);
	//this->listOfEntities.push_back(cubo1);

	//cubo1 = new Model("objs/box.obj", "textures/verde.jpg");
	//cubo1->setScale(vec3(1, 0.1, 1));
	//cubo1->setTranslate(peaoMax);
	//cubo1->SetWireframe(true);
	//this->listOfEntities.push_back(cubo1);

	//cubo1 = new Model("objs/box.obj", "textures/branco.jpg");
	//cubo1->setScale(vec3(1, 0.1, 1));
	//cubo1->setTranslate(peaoMin);
	//cubo1->SetWireframe(true);
	//this->listOfEntities.push_back(cubo1);

	/* Initilize the Animators */

	this->leftArm->setAnimator(ptrAnimatorLeftArm);
	this->leftForearm->setAnimator(ptrAnimatorLeftForearm);

	this->rightArm->setAnimator(ptrAnimatorRightArm);
	this->rightForearm->setAnimator(ptrAnimatorRightForearm);

	this->rightLeg->setAnimator(ptrAnimatorRighLeg);
	this->leftLeg->setAnimator(ptrAnimatorLeftLeg);

}
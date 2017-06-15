/************************************************************************/
/* File: Joint.cpp                                                      */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

/* Basic Includes */
#include "stdafx.h"
#include "Joint.h"

/* Standard Includes */
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>

/* GLM Includes */
#include <glm/gtc/matrix_transform.hpp>

/* Utility Includes */
#include "Constants.h"
#include "Application.h"

/**
\brief Construtor para a classe Joint
Cria uma entidade posicionada na origem, orientada sobre os eixos cartesianos e
em escala canonica.
*/
Joint::Joint() : Entity()
{}
/**
\brief Construtor de clonagem para a classe Joint
Cria uma copia exata de um objeto entidade ja existente
\param clone Objeto a ser clonado
*/
Joint::Joint(const Joint& clone) : Entity(clone)
{}
/**
\brief Construtor de clonagem para a classe Joint a partir de ponteiros
Cria uma copia exata de um objeto entidade ja existente
\param ptrClone Ponteiro para o objeto a ser clonado
*/
Joint::Joint(Joint* ptrClone) : Entity(ptrClone)
{}
/**
\brief Desaloca os objetos dinamicos desta classe
*/
Joint::~Joint()
{
	for (vector<Joint*>::iterator itJoint = this->listOfJoints.begin(); itJoint != this->listOfJoints.end(); itJoint++)
		delete (*itJoint);
}
/**
\brief Associa uma nova junta como filha desta junta
\param ptrJoint ponteiro para a nova junta-filha a ser associada
*/
void Joint::Attach(Joint* ptrJoint)
{
	if (ptrJoint) {
		this->listOfJoints.push_back(ptrJoint);
		ptrJoint->setRoot(this);
	}
}

/**
\brief Desassocia uma nova junta como filha desta junta
\param ptrJoint ponteiro para a ser desassociado
*/
void Joint::Dettach(int indx)
{
	vector<Joint*>::iterator erased = listOfJoints.erase(listOfJoints.begin() + indx);
	(*erased)->setTranslate(this->getTranslate());
	ptrApp->AddEntity(*erased);
}
/**
\brief Desassocia uma nova junta como filha desta junta
\param ptrJoint ponteiro para a ser desassociado
*/
int Joint::GetIndexOf(Joint* joint) {
	for (int i = 0; i < this->listOfJoints.size(); ++i)
		if (this->listOfJoints.at(i) == joint)
			return i;
	return -1;
}	

/**
\brief Rotina para rendering de todas as primitivas graficas que compoem esta junta
*/
void Joint::OnPreRender(glm::mat4 _m4ModelMatrix)
{

	m4JointModelMatrix = glm::rotate(_m4ModelMatrix, glm::radians(this->vRotatePivot.z), glm::vec3(0.0f, 0.0f, 1.0f));
	m4JointModelMatrix = glm::rotate(m4JointModelMatrix, glm::radians(this->vRotatePivot.y), glm::vec3(0.0f, 1.0f, 0.0f));
	m4JointModelMatrix = glm::rotate(m4JointModelMatrix, glm::radians(this->vRotatePivot.x), glm::vec3(1.0f, 0.0f, 0.0f));

	m4JointModelMatrix = glm::translate(m4JointModelMatrix, this->vPivot);

	m4JointModelMatrix = glm::translate(m4JointModelMatrix, this->vTranslate) * glm::toMat4(qOrientation);
	

	for (vector<Joint*>::iterator itJoint = this->listOfJoints.begin(); itJoint != this->listOfJoints.end(); itJoint++)
		(*itJoint)->OnPreRender(m4JointModelMatrix);

	m4ModelMatrix = glm::scale(m4JointModelMatrix, this->vScale);
	m4ModelMatrix = glm::translate(m4ModelMatrix, this->vPivot * -1.0f);

	for (vector<Entity*>::iterator itEntity = this->listOfEntities.begin(); itEntity != this->listOfEntities.end(); itEntity++)
		(*itEntity)->OnPreRender(m4ModelMatrix);

}

/**
\brief Rotina para rendering de todas as primitivas graficas que compoem esta junta
*/
void Joint::OnRender(glm::mat4 m4ModelMatrix)
{
	for (vector<Joint*>::iterator itJoint = this->listOfJoints.begin(); itJoint != this->listOfJoints.end(); itJoint++)
		(*itJoint)->OnRender(m4JointModelMatrix);


	for (vector<Entity*>::iterator itEntity = this->listOfEntities.begin(); itEntity != this->listOfEntities.end(); itEntity++)
		(*itEntity)->OnRender(m4ModelMatrix);

}

/**
\brief Carrega as dimensoes do modelo
*/
void Joint::LoadDimensions() {

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
	for (vector<Joint*>::iterator pointer = this->listOfJoints.begin(); pointer != this->listOfJoints.end(); pointer++) {
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
/**
\brief Executa o processo de animação
\param dDeltaTime tempo transcorrido deste a ultima chamada desta função
*/
void Joint::OnLoop(double dDeltaTime)
{
	for (vector<Joint*>::iterator itJoint = this->listOfJoints.begin(); itJoint != this->listOfJoints.end(); itJoint++)
		(*itJoint)->OnLoop(dDeltaTime);

	Entity::OnLoop(dDeltaTime); // chama a mesma rotina no objeto-base
}
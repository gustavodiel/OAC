/************************************************************************/
/* File: Joint.h                                                        */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

/* Utility Includes */
#include "Entity.h"

#include <vector>

/**
\class Joint
\brief Responsavel por gerenciar atores com articulacao
*/
class Joint : public Entity
{
protected:
	std::vector<Joint*> listOfJoints; ///< lista de juntas filhas associadas a esta junta

	glm::mat4		m4JointModelMatrix;

public:
	Joint();
	Joint(const Joint &);
	Joint(Joint*);
	~Joint();

	virtual void Initialize() {}

	/**
	\brief Associa uma nova junta como filha desta junta
	\param ptrJoint ponteiro para a nova junta-filha a ser associada
	*/
	void Attach(Joint*);

	/**
	\brief Desassocia uma nova junta como filha desta junta
	\param ptrJoint ponteiro para a ser desassociado
	*/
	void Dettach(int);
	int GetIndexOf(Joint*);

	/**
	\brief Rotina para renderizacao de sombra de todas as primitivas graficas que compoem esta junta
	*/
	virtual void OnPreRender(glm::mat4);

	/**
	\brief Rotina para rendering de todas as primitivas graficas que compoem esta junta
	*/
	virtual void OnRender(glm::mat4);

	/**
	\brief Executa o processo de animação
	\param dDeltaTime tempo transcorrido deste a ultima chamada desta função
	*/
	virtual void OnLoop(double);

	/**
	\brief Carrega as dimensoes do modelo
	*/
	virtual void LoadDimensions();
};


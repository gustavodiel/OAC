/************************************************************************/
/* File: Model.h                                                        */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

/* OpenGL Includes */
#include <Windows.h>
#include <GL/glew.h>
#include <gl/gl.h>

/* Standard Includes */
#include <vector>

/* GLM Includes */
#include <glm/glm.hpp>

/* Utility Includes */
#include "Material.h"
#include "Entity.h"
#include "Application.h"

/**
\class Model
\brief Responsavel por carregar, preparar e renderizar os models importados de um arquivo.
*/
class Model : public Entity
{
private:
	Material* ptrMaterial;							//!< ponteiro para o material do modelo

	bool bIsShearable = false;						//!< booleano para saber se ocorre o shearing no modelo
	float fShearAmountA = 0;						//!< indice de shearing A
	float fShearAmountB = 0;						//!< indice de shearing B

	std::vector<glm::vec3> v3Vertices;				//!< vertices do modelo
	std::vector<glm::vec2> v3UVs;					//!< cordenadas UV do modelo
	std::vector<glm::vec3> v3Normals;				//!< normais do modelo

	GLuint uiElementBufferId;						//!< id do buffer do elemento ( topologia ) do modelo
	GLuint uiNormalBufferId;						//!< id do buffer de Normais
	GLuint uiUVBufferId;							//!< id do buffer de UVs
	GLuint uiVertexBufferId;						//!< id do buffer de Vertices

	std::vector<unsigned short> vuiIndices;			//!< vetor de indices


public:
	Model(const char*, const char*, vec3 ambient = vec3(0.1, 0.1, 0.1), vec3 specular = vec3(0.15, 0.15, 0.15));
	Model() {};
	~Model();

	/**
	\brief Rotina de renderizacao de sombra do objeto em OPENGL.
	*/
	void OnPreRender(glm::mat4);

	/**
	\brief Rotina de renderizacao do objeto em OPENGL.
	*/
	void OnRender(glm::mat4);

	/**
	\brief Retorna o material do modelo
	\return ponteiro do material
	*/
	inline Material* getMaterial() { return this->ptrMaterial; };

	/**
	\brief Define o material do modelo
	\param mat ponteiro do material
	*/
	Material* setMaterial(Material* mat) { this->ptrMaterial = mat; };
	
	/**
	\brief Define se o modelo sofre shearing ( balancar )
	\param is booleano se sofre ou nao
	*/
	void setShearable(bool is) { this->bIsShearable = is; };

	/**
	\brief Define a quantidade de shearing do modelo
	\param a float pra a quantidade A
	\param b float para a quantidade B
	*/
	void setShear(float a, float b) { this->fShearAmountA = a; this->fShearAmountB = b; };

	/**
	\brief Carrega as dimensoes do modelo
	*/
	void LoadDimensions();

	/**
	\brief Executa um loop para atualizar toda a logica do modelo
	*/
	void OnLoop(double);

};


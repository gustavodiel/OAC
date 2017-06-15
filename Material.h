/************************************************************************/
/* File: Material.h                                                     */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

/* GLM Includes */
#include <glm/glm.hpp>

/**
\class Material
\brief Responsavel por armazenar todas as propriedades do material
*/
class Material
{
public:
	Material(const char*, glm::vec3, glm::vec3, float alpha);
	~Material();

	/**
	\brief Altera a cor Ambiente
	\param color cor ambiente
	*/
	void SetAmbientColor(glm::vec3 color);

	/**
	\brief Altera a cor Ambiente
	\param r cor vermelha
	\param g cor verde
	\param b cor azul
	*/
	void SetAmbientColor(float r, float g, float b);


	/**
	\brief Altera a cor Specular
	\param color cor Specular
	*/
	void SetSpecularColor(glm::vec3);

	/**
	\brief Altera a cor Specular
	\param r cor vermelha
	\param g cor verde
	\param b cor azul
	*/
	void SetSpecularColor(float r, float g, float b);

	/**
	\brief Altera o alpha do material
	\param alpha indice alpha
	*/
	void SetAlpha(float alphaa);

	/**
	\brief Define a textura do material
	\param texture caminho para a textura
	*/
	void SetTexture(const char* texture);

	/**
	\brief Retorna a cor Ambiente
	\return vec3 com cor ambiente
	*/
	inline glm::vec3 GetAmbientColor() { return this->v3AmbientColor; };

	/**
	\brief Retorna a cor Specular
	\return vec3 com cor Specular
	*/
	inline glm::vec3 GetSpecularColor() { return this->v3SpecularColor; };

	/**
	\brief Retorna o alpha do material
	\return float com alpha
	*/
	inline float GetAlpha() { return this->fAlpha; };

	/**
	\brief Retorna id da textura
	\return unsigned int com o id da textura
	*/
	inline unsigned int GetTextureId() { return this->uiTextureId; };

protected:
	glm::vec3 v3AmbientColor;		//!< cor ambiente
	glm::vec3 v3SpecularColor;		//!< cor specular

	float fAlpha;					//!< alpha do material

	unsigned int uiTextureId;		//!< id da textura
};


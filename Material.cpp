/************************************************************************/
/* File: Material.cpp                                                   */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

/* Basic Includes */
#include "stdafx.h"
#include "Material.h"

/* Utility Includes */
#include "Constants.h"
#include "TextureLoader.h"


Material::Material(const char* texture, glm::vec3 ambient, glm::vec3 specular, float alpha)
{
	this->v3AmbientColor = ambient;
	this->v3SpecularColor = specular;
	this->fAlpha = alpha;
	this->uiTextureId = ptrTextureLoader->LoadTexture(texture);
}

Material::~Material()
{
}

/**
\brief Altera a cor Ambiente
\param color cor ambiente
*/
void Material::SetAmbientColor(glm::vec3 color) {
	this->v3AmbientColor = color;
}

/**
\brief Altera a cor Ambiente
\param r cor vermelha
\param g cor verde
\param b cor azul
*/
void Material::SetAmbientColor(float r, float g, float b) {
	this->v3AmbientColor = vec3(r, g, b);
}

/**
\brief Altera a cor Specular
\param color cor Specular
*/
void Material::SetSpecularColor(glm::vec3 color) {
	this->v3SpecularColor = color;
}

/**
\brief Altera a cor Specular
\param r cor vermelha
\param g cor verde
\param b cor azul
*/
void Material::SetSpecularColor(float r, float g, float b) {
	this->v3SpecularColor = vec3(r, g, b);
}

/**
\brief Altera o alpha do material
\param alpha indice alpha
*/
void Material::SetAlpha(float alpha) {
	this->fAlpha = alpha;
}

/**
\brief Define a textura do material
\param texture caminho para a textura
*/
void Material::SetTexture(const char* texture) {
	this->uiTextureId = ptrTextureLoader->LoadTexture(texture);
}
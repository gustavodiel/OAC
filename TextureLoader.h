/************************************************************************/
/* File: TextureLoader.h                                                */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

/* Standard Includes */
#include <map>
#include <string>
#include <vector>

/**
\class TextureLoader
\brief Responsavel por carrega as texturas utilizando a biblioteca SOIL, e tambem salva elas para que nao precisem ser carregadas novamente
*/
class TextureLoader
{

protected:

	std::map<std::string, GLuint> loaded;			//!< map para salvar em memoria todos os objetos ja carregados para acelerar carregamento futuro

public:

	TextureLoader();
	~TextureLoader();

	/**
	\brief Carrega a textura
	\param filename caminho ate o arquivo de textura
	\return unsigned int que e o id da textura
	*/
	GLuint LoadTexture(std::string filename);

	/**
	\brief Carrega a textura como cubemap
	\param filename caminho ate o arquivo de textura
	\return unsigned int que e o id da textura
	*/
	GLuint loadCubemap(std::vector<const GLchar*> faces);

};


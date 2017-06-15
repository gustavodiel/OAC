/************************************************************************/
/* File: OBJLoader.h                                                    */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

/* Standart Includes */
#include <vector>
#include <map>
#include <string>

/* GLM Include */
#include <glm/glm.hpp>

/**
\struct ObjectStruct
\brief Struct feita para armazenar as informacoes do objeto carregado, ja processadas.
\var ObjectStruct::vertices
Lista de vetores 3 com os vertices do objeto
\var ObjectStruct::normals
Lista de vetores 3 com as normais do objeto
\var ObjectStruct::uvs
Lista de vetores 2 com os mapeamentos uv do objeto
\var ObjectStruct::indices
Lista de unsigned short com os de indices para os vertices do objeto
\var ObjectStruct::vMinValue
Vetor 3 com a menor posicao espacial do objeto
\var ObjectStruct::vMaxValue
Vetor 3 com a maior posicao espacial do objeto
\var ObjectStruct::vCenter
Vetor 3 com o centro do objeto
*/
typedef struct objStruct {

	std::vector<glm::vec3>			v3Vertices;		//!< vertices do objeto
	std::vector<glm::vec3>			v3Normals;		//!< normais do objeto

	std::vector<glm::vec2>			v3UVs;			//!< mapeamento UV do objeto ( para texturas )

	std::vector<unsigned short>		vuiIndices;		//!< indices para relacionar com os vertices

	glm::vec3			vMinValue;			//!< posicao mais baixa do objeto
	glm::vec3			vMaxValue;			//!< posicao mais alta do objeto
	glm::vec3			vCenter;			//!< centro do objeto

} ObjectStruct;

/**
\class OBJLoader
\brief Responsavel por carregar diversos tipos modelos na memoria, e processar para buscar as informacoes desejadas
*/
class OBJLoader
{

protected:

	std::map<std::string, ObjectStruct> loaded;		//!< map para salvar em memoria todos os objetos ja carregados para acelerar carregamento futuro

public:
	OBJLoader();
	~OBJLoader();

	/**
	\brief Carrega um modelo usando a biblioteca AssImp
	\param filename caminho ate o arquivo do model. Suporta diversos tipos de arquivos
	\return struct com todas as informacoes do arquivo.
	*/
	ObjectStruct LoadAssImp(std::string filename);

};


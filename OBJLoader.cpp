/************************************************************************/
/* File: OBJLoader.cpp                                                  */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

/* Basic Includes */
#include "stdafx.h"
#include "OBJLoader.h"

/* Standard Includes */
#include <stdio.h>
#include <cstring>

/* AssImp Includes */
#include <assimp\Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing flags

OBJLoader::OBJLoader()
{
}

OBJLoader::~OBJLoader()
{
}

/**
\brief Carrega um modelo usando a biblioteca AssImp
\param filename caminho ate o arquivo do model. Suporta diversos tipos de arquivos
\return struct com todas as informacoes do arquivo.
*/
ObjectStruct OBJLoader::LoadAssImp(std::string filename) {
	if (loaded.count(filename)) {
		return loaded[filename];
	}

	const char * path = filename.c_str();

	printf("Loading %s\n", path);

	std::vector<unsigned short> vuiIndices;
	std::vector<glm::vec3> v3Vertices;
	std::vector<glm::vec2> v3UVs;
	std::vector<glm::vec3> v3Normals;

	ObjectStruct ret;

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path, 
		aiProcess_GenSmoothNormals |
		aiProcess_ImproveCacheLocality |
		aiProcess_OptimizeGraph |
		aiProcess_FixInfacingNormals |
		aiProcess_GenUVCoords |
		aiProcess_OptimizeMeshes |
		aiProcess_SortByPType |
		aiProcess_ValidateDataStructure |
		aiProcess_FlipUVs |
		aiProcess_Triangulate);

	if (!scene) {
		fprintf(stderr, importer.GetErrorString());
		getchar();
		return ret;
	}

	int tFaces = 0;

	glm::vec3 maxVertex = glm::vec3(-9999.0f, -9999.0f, -9999.0f);
	glm::vec3 minVertex = maxVertex * -1.0f;

	for (int m = 0; m < scene->mNumMeshes; m++) {
		const aiMesh* mesh = scene->mMeshes[m]; // In this simple example code we always use the 1rst mesh (in OBJ files there is often only one anyway)

		tFaces += mesh->mNumFaces;
												// Fill vertices positions
		//vertices.reserve(mesh->mNumVertices);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			aiVector3D pos = mesh->mVertices[i];
			v3Vertices.push_back(glm::vec3(pos.x, pos.y, pos.z));
			if (minVertex.x > pos.x) minVertex.x = pos.x;
			if (minVertex.y > pos.y) minVertex.y = pos.y;
			if (minVertex.z > pos.z) minVertex.z = pos.z;
			if (maxVertex.x < pos.x) maxVertex.x = pos.x;
			if (maxVertex.y < pos.y) maxVertex.y = pos.y;
			if (maxVertex.z < pos.z) maxVertex.z = pos.z;
		}

		// Fill vertices texture coordinates
		if (mesh->HasTextureCoords(0)) {
			v3UVs.reserve( mesh->mNumVertices);
			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				aiVector3D UVW = mesh->mTextureCoords[0][i]; // Assume only 1 set of UV coords; AssImp supports 8 UV sets.
				v3UVs.push_back(glm::vec2(UVW.x, UVW.y));
			}
		}
		else {
			printf("Has no Texture Coords\n");
		}

		// Fill vertices normals
		//normals.reserve(mesh->mNumVertices);
		for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
			aiVector3D n = mesh->mNormals[i];
			v3Normals.push_back(glm::vec3(n.x, n.y, n.z));
		}


		// Fill face indices
		//indices.reserve(3 * mesh->mNumFaces);
		for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
			for (int ind = 0; ind < mesh->mFaces[i].mNumIndices; ++ind) {
				vuiIndices.push_back(mesh->mFaces[i].mIndices[ind]);
			}
		}
	}

	ret.vuiIndices = vuiIndices;
	ret.v3Vertices = v3Vertices;
	ret.v3UVs =  v3UVs;
	ret.v3Normals = v3Normals;
	ret.vMaxValue = maxVertex;
	ret.vMinValue = minVertex;

	printf("%s carregado com %d vertices, %d indices e %d faces\n", filename.c_str(), v3Vertices.size(), vuiIndices.size(), tFaces);
	printf("Tamanho do %s: min: [%lf, %lf, %lf] | max: [%lf, %lf, %lf]\n", filename.c_str(), minVertex.x, minVertex.y, minVertex.z, maxVertex.x, maxVertex.y, maxVertex.z);

	// The "scene" pointer will be deleted automatically by "importer"

	loaded[filename] = ret;

	return ret;
}

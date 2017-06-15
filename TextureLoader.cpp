/************************************************************************/
/* File: TextureLoader.cpp                                              */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

/* Basic Includes */
#include "stdafx.h"

/* Standard Includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* OpenGL Includes */
#include <GL/glew.h>
#include <GLFW\glfw3.h>

/* SOIL Includes */
#include <SOIL\SOIL.h>

/* Self Include */
#include "TextureLoader.h"


TextureLoader::TextureLoader()
{

}


TextureLoader::~TextureLoader()
{
}

/**
\brief Carrega a textura
\param filename caminho ate o arquivo de textura
\return unsigned int que e o id da textura
*/
GLuint TextureLoader::LoadTexture(std::string filename)
{
	if (loaded.count(filename)) {
		return loaded[filename];
	}

	const char* texName = filename.c_str();

	printf("Loading: %s\n", texName);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_2D, textureID);

	image = SOIL_load_image(texName, &width, &height, 0, SOIL_LOAD_RGBA);	

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);

	loaded[filename] = textureID;
	return textureID;

}


/**
\brief Carrega a textura como cubemap
\param filename caminho ate o arquivo de textura
\return unsigned int que e o id da textura
*/
GLuint TextureLoader::loadCubemap(std::vector<const GLchar*> faces)
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);

	int width, height;
	unsigned char* image;

	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	for (GLuint i = 0; i < faces.size(); i++)
	{
		image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}

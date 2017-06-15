/************************************************************************/
/* File: Shader.h                                                       */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

/* Standard Includes */
#include <windows.h>

/* OpenGL Includes */
#include <gl/gl.h>

/**
\class Shader
\brief Responsavel por carregar, compilar e informar possiveis erros de compilacao do shader
*/
class Shader
{
public:
	Shader();
	~Shader();

	/**
	\brief carrega os dois shaders, une os dois e entao compila eles
	\param vertex_file_path arquivo do shader de vertice
	\param fragment_file_path arquivo do shader de fragmento
	\return unsigned int com o id do programa gerado pelos dois shaders
	*/
	GLuint LoadShaders(const char *vertex_file_path, const char *fragment_file_path);
};


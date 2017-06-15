/************************************************************************/
/* File: Cloth.h                                                        */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

/* Basic Includes */
#pragma once
#include "Entity.h"

/* Physics Includes */
#include "Vertice3D.h"
#include "Juncao.h"

/* Utility Includes */
#include "Material.h"
#include "Utilities.hpp"

/**
\class Cloth
\brief Classe encarregada de gerar, gerenciar e renderizar tecido
*/
class Cloth :
	public Entity
{
public:
	Cloth(float width, float height, int num_particles_width, int num_particles_height);
	~Cloth();

	/**
	\brief Rotina de renderizacao de sombra do objeto em OPENGL.
	*/
	void OnPreRender(glm::mat4);

	/**
	\brief Rotina de renderizacao do objeto em OPENGL.
	*/
	void OnRender(glm::mat4);

	/**
	\brief Executa um loop para atualizar toda a logica do modelo
	*/
	void OnLoop(double);

	/**
	\brief Adiciona uma forca na malha no tempo que a funcao e chamada
	\param direction vetor 3 contendo a direcao da forca
	*/
	void AddForce(const vec3 direction);

	/**
	\brief Adiciona uma forca na malha em um tempo determinado
	\param direction vetor 3 contendo a direcao da forca
	\param time double indicando o tempo para adicionar a forca
	*/
	void AddForce(const vec3 direction, double time);

	/**
	\brief Adiciona uma forca de vento na malha no tempo que a funcao e chamada
	\param direction vetor 3 contendo a direcao do vento
	*/
	void WindForce(const vec3 direction);

	/**
	\brief Adiciona uma forca de vento na malha em um tempo determinado
	\param direction vetor 3 contendo a direcao do vento
	\param time double indicando o tempo para adicionar o vento
	*/
	void WindForce(const vec3 direction, double time);

	/**
	\brief Faz os ajustes iniciais, como carregar a malha e material.
	*/
	void Initialize() {};

	/**
	\brief Retorna o material da malha
	\return ponteiro de Material que aponta para o material utilizado
	*/
	inline Material* GetMaterial() { return this->ptrMaterial; };

	/**
	\brief Muda o material da malha para o material especificado
	\param mat material especificado
	*/
	void SetMaterial(Material* mat) { this->ptrMaterial = mat; };

	/**
	\brief Adiciona uma forca deteccao de colisao com esfera
	\param center centro da esfera
	\param radius raio da esfera
	*/
	void ProcessBallCollision(const glm::vec3 center, const float radius);

	/**
	\brief Ajusta a gravidade
	\param grav direcao e forca da gravidade
	*/
	void SetGravity(vec3 grav) { this->vGravity = grav; };

	/**
	\brief Ajusta o vento
	\param wind direcao e forca do vento
	*/
	void SetWind(vec3 wind) { this->vWind = wind; };

private:

	/**
	\struct Vertex
	\brief Struct feita para armazenar as informacoes dos vertices da malha.
	\var ObjectStruct::position
	vetor 3 com a posicao do vertice
	\var ObjectStruct::uv
	vetor 2 com a identificacao de UV do vertice
	\var ObjectStruct::normal
	vetor 3 com a normal do vertice
	*/
	struct Vertex {
		vec3 position;								//!< posicao do vertice
		vec2 uv;									//!< coordenadas UV do vertice
		vec3 normal;								//!< Normal do vertice
	};

	std::vector<Utilities::TimeForce> vTimedForces;		//!< lista de forcas com tempo para serem executadas
	std::vector<Utilities::TimeForce> vTimedWind;		//!< lista de forcas de vento para serem executadas

	std::vector<Vertice3D> particles;				//!< vertices que fazem parte da malha

	std::vector<Juncao> constraints;				//!< todas as juntas entre os vertices da malha

	glm::vec3 vGravity;								//!< gravidade atuando na malha
	glm::vec3 vWind;								//!< vento atuando constantemente na malha

	int num_particles_width;						//!< numero de particulas na malha na horizontal
	int num_particles_height;						//!< numero de particulas na malha na vertical

	GLuint uiElementArrayBufferId;					//!< id do buffer do elemento a ser desenhado
	GLuint uiTextureId;								//!< id da textura da malha	
	GLuint uiPositionAttributeLocation;				//!< posicao na memoria da GPU do atributo de posicoes do vertice
	GLuint uiUVAttributeLocation;					//!< posicao na memoria da GPU do atributo de UV do vertice
	GLuint uiNormalAttributeLocation;				//!< posicao na memoria da GPU do atributo de Normal do vertice
	GLuint uiNormalBufferId;						//!< id do buffer de normais
	GLuint uiUVBufferId;							//!< id do buffer de UVs
	GLuint uiVertexBufferId;						//!< id do buffer de vertices

	bool bLoaded = false;							//!< boolean para definir se a malha foi ou nao carregada

	int iElementSize;								//!< quantidade de elementos a serem desenhados
		
	Material* ptrMaterial;							//!< material da malha

	mat4 m4ModelMatrix;								//!< matriz de trasnforamcao da malha


	/**
	\brief Retorna o indice do vertice
	\param x posicao horizontal na malha
	\param y posicao vertical na malha
	\return inteiro com o indice do vertice
	*/
	inline int GetVerticeIndex(int x, int y) { return y*num_particles_width + x; };

	/**
	\brief Retorna o vertice
	\param x posicao horizontal na malha
	\param y posicao vertical na malha
	\return vertice que esta na posicao x, y na malha
	*/
	inline Vertice3D* GetVertice(int x, int y) { return &particles[GetVerticeIndex(x, y)]; };

	/**
	\brief Recalcula todas as juncoes entre os vertices e controla para que nao deforme demais
	\param p1 vertice 1
	\param p2 vertice 2
	*/
	void MakeConstraint(Vertice3D *p1, Vertice3D *p2);


	/**
	\brief Retorna o normal de um triangulo entre tres vertices
	\param p1 primeiro vertice
	\param p2 segundo vertice
	\param p3 terceiro vertice
	\return vetor 3 com a normal do triangulo formado
	*/
	vec3 GerarNormalTriangulo(Vertice3D *p1, Vertice3D *p2, Vertice3D *p3);


	/**
	\brief Calcula a forca de vento em um triangulo
	\param p1 vertice 1
	\param p2 vertice 2
	\param p3 vertice 3
	\param direction direcao do vento
	*/
	void AddWindToTriangle(Vertice3D *p1, Vertice3D *p2, Vertice3D *p3, const vec3 direction);

	/**
	\brief Cria um triangulo com o uv
	\param p1 vertice
	\param uv uv do vertice
	\param vertexData lista para adicionar os triangulos
	*/
	void CreateTriangle(Vertice3D *p1, const vec2 uv, std::vector<Vertex> &vertexData);

};

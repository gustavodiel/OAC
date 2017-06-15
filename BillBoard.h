/************************************************************************/
/* File: TesteGL.cpp                                                    */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

#include "Entity2D.h"

/* GLM Includes */
#include <glm/glm.hpp>

class BillBoard: public Entity2D
{

public:

protected:

	unsigned int			uiTextureId;			//!< Id da textura do billboard
	static unsigned int		uiVertexBufferId;		//!< id do buffer de vertices
	static bool				bHasAnyLoaded;			//!< para saber se algum billboard foi carregado

	float					fDeltaShear;

	bool					bIsShearable;			//!< ele move com o vento ( grama e tals )

	glm::vec3				v3Position;				//!< posicao do billboard no mundo

	glm::vec2				v2Size;					//!< tamanho do billboard

public:
	//************************************
	// Method:    BillBoard
	// FullName:  BillBoard::BillBoard
	// Access:    public 
	// Parameter: const char * texture is the path for the texture file of this billboard
	//************************************
	BillBoard(const char* texture = "textures/grass.png");
	~BillBoard();

	//************************************
	// Method:    OnPreRender
	// FullName:  BillBoard::OnPreRender
	// Access:    public 
	// Returns:   void
	// Qualifier: Renderiza a sombra
	// Parameter: glm::mat4 
	//************************************
	void OnPreRender(glm::mat4);
	//************************************
	// Method:    OnRender
	// FullName:  BillBoard::OnRender
	// Access:    public 
	// Returns:   void
	// Qualifier: Renderiza o modelo
	// Parameter: glm::mat4 matriz do modelo
	//************************************
	void OnRender(glm::mat4);

	//************************************
	// Method:    setTranslate
	// FullName:  BillBoard::SetTranslate
	// Access:    public 
	// Returns:   void
	// Qualifier: Translada o objeto
	// Parameter: glm::vec3 translate posicao
	//************************************
	void setTranslate(glm::vec3 translate);
	//************************************
	// Method:    SetSize
	// FullName:  BillBoard::SetSize
	// Access:    public 
	// Returns:   void
	// Qualifier: Define o tamanho do objeto
	// Parameter: glm::vec3 size tamanho
	//************************************
	void SetSize(glm::vec2 size);

	//************************************
	// Method:    OnLoop
	// FullName:  BillBoard::OnLoop
	// Access:    public 
	// Returns:   void
	// Qualifier: Atualiza o objeto
	// Parameter: double dDeltaTime tempo decorrido desde a ultima atualizacao
	//************************************
	void OnLoop(double dDeltaTime);

	//************************************
	// Method:    SetShearable
	// FullName:  BillBoard::SetShearable
	// Access:    public 
	// Returns:   void
	// Qualifier: Seta se o objeto é ou nao shearable ( nao se a traducao :x )
	// Parameter: bool bShear
	//************************************
	void SetShearable(bool bShear);


};


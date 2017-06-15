/************************************************************************/
/* File: Cloud.h                                                        */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

#include "Entity.h"
#include "Actor2D.h"

class Cloud :
	public Actor2D
{
public:
	Cloud(const char* texture);
	~Cloud();
	
	virtual void setTranslate(glm::vec3) override;

	virtual void OnLoop(double) override;


	virtual void LoadDimensions() override;


	virtual void OnPreRender(glm::mat4) override;


	virtual void OnRender(glm::mat4) override;

	void setSize(vec2);

private:

	class BillBoard			*bpCloud;

};


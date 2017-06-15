/************************************************************************/
/* File: BodyMember.h                                                   */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once
#include "Joint.h"

class BodyMember :
	public Joint
{
public:
	BodyMember(const char* cor) : myCor(cor) { this->Initialize(); };
	~BodyMember() {};

	virtual void Initialize();

private:
	const char* myCor;
};


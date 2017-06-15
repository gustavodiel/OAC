/************************************************************************/
/* File: Pessoa.h                                                       */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

#include "Joint.h"

class Pessoa :
	public Joint
{
public:
	Pessoa();
	~Pessoa();

	virtual void Initialize();

	inline class BodyMember* getRightArm() { return this->rightArm; };
	inline class BodyMember* getLeftArm() { return this->leftArm; };
	inline class BodyMember* getRightForearm() { return this->rightForearm; };
	inline class BodyMember* getLeftForearm() { return this->leftForearm; };
	inline class BodyMember* getRightLeg() { return this->rightLeg; };
	inline class BodyMember* getLeftLeg() { return this->leftLeg; };

	void addWalk(double, double, double);

	class Animator *  ptrAnimatorLeftArm;
	class Animator *  ptrAnimatorLeftForearm;
	class Animator *  ptrAnimatorRightArm;
	class Animator *  ptrAnimatorRightForearm;
	class Animator *  ptrAnimatorLeftLeg;
	class Animator *  ptrAnimatorRighLeg;

protected:
	class BodyMember* rightArm;
	class BodyMember* leftArm;
	class BodyMember* rightForearm;
	class BodyMember* leftForearm;
	class BodyMember* rightLeg;
	class BodyMember* leftLeg;

};
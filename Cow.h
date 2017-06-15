/************************************************************************/
/* File: Cow.h                                                          */
/* Autor: Gustavo Diel                                                  */
/* License: WTFLP                                                       */
/************************************************************************/

#pragma once

#include "Joint.h"

class Cow :
	public Joint
{
public:
	Cow();
	~Cow();

	virtual void Initialize();  

	inline class BodyMember* getFrontRightLeg() { return this->frontRightLeg; };
	inline class BodyMember* getFrontLeftLeg() { return this->frontLeftLeg; };
	inline class BodyMember* getBackRightLeg() { return this->backRightLeg; };
	inline class BodyMember* getBackLeftLeg() { return this->backLeftLeg; };

	void addWalk(double, double, double);

protected:
	class BodyMember* frontLeftLeg;
	class BodyMember* frontRightLeg;
	class BodyMember* backRightLeg;
	class BodyMember* backLeftLeg;

	class Animator *  ptrAnimatorFrontLeftLeg;
	class Animator *  ptrAnimatorFrontRightLeg;
	class Animator *  ptrAnimatorBackLeftLeg;
	class Animator *  ptrAnimatorBackRightLeg;
	class Animator *  ptrAnimatorSelf;
};


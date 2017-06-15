#pragma once
#include <vector>
using namespace std;

#include "Entity.h"
#include "Interpolator.h"

/**
\class Animator
\brief Classe que implementa uma anima��o pose-to-pose com base em uma serie de interpoladores
\sa Interpolator
*/
class Animator
{
public:
	/**
	\brief Lista de possiveis tipos de anima��es suportados
	*/
	enum AnimationType {
		ONCE = 0,  ///< execute a linha de tempo uma vez e para o processo de anima��o
		LOOP       ///< executa o processo de anima��o de forma ciclica
	};

	Animator(Animator::AnimationType = Animator::ONCE);
	Animator(const Animator &);
	Animator(Animator *);
	~Animator();

	void setParent(Entity*);
	void OnLoop(double);
	void addInterpolator(Interpolator*);
protected:
	Entity *					ptrOwner;            ///< ponteiro para o objeto que sera afetado por este Animator
	AnimationType				animationType;       ///< tipo de anima��o executada por este animador
	double						dAnimationTime,      ///< tempo acumulado deste o inicio do processo de anima��o
								dAnimationDuration;  ///< dura��o da anima��o em segundos

	bool						bStopUpdating = false;
	vector<Interpolator*>		listOfInterpolators; ///< lista de interpoladores que compoem esta anima��o

};

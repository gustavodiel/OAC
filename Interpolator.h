#pragma once
#include <vector>

using namespace std;

/**
\class Interpolator
\brief Classe que implementa um interpolador entre um conjunto de atributos dados
\sa Pose
*/
class Interpolator
{
protected:
	class Entity *          ptrOwner;       ///< ponteiro para o objeto que sera afetado por este interpolador
	vector<class PoseAttr*> listOfPoseAttr; ///< lista de atributos interpoláveis associados a este interpolador

	void updateParent(class Entity *);

public:
	Interpolator();
	Interpolator(const Interpolator &);
	Interpolator(Interpolator *);
	virtual ~Interpolator() = 0;

	void setParent(class Entity *);
	void addAttribute(class PoseAttr *);
	class PoseAttr * getAttribute(unsigned int);
	/**
	\brief Retorna a quantidade de atributos associados a este interpolador
	\return tamanho de lista de atributos
	*/
	inline unsigned int getNumberOfAttr() { return (int)this->listOfPoseAttr.size(); }

	virtual void OnLoop(double) = 0;
};

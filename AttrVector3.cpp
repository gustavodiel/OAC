#include "stdafx.h"
#include "AttrVector3.h"

#include "Entity.h"

/**
\brief Construtor para a classe AttrVector3
\param dAttrTime tempo (em segundos) na timeline para este atributo interpolável
\param attrName define o nome do componente que será afetado por este atributo interpolavel
*/
AttrVector3::AttrVector3(double dAttrTime, AttrVector3::AttrName attrName) : PoseAttr(dAttrTime, attrName)
{}
/**
\brief Construtor para a classe AttrVector3
\param Value define o valor inicial para o atributo interpolavel
\param dAttrTime tempo (em segundos) na timeline para este atributo interpolável
\param attrName define o nome do componente que será afetado por este atributo interpolavel
*/
AttrVector3::AttrVector3(glm::vec3 Value, double dAttrTime, AttrVector3::AttrName attrName) : PoseAttr(dAttrTime, attrName)
{
	this->Value = Value;
}
/**
\brief Copy-constructor para a classe AttrVector3 baseado em ponteiros
\param ptrClone ponteiro para o objeto a ser clonado
*/
AttrVector3::AttrVector3(AttrVector3 * ptrClone) : PoseAttr(ptrClone)
{
	this->Value = ptrClone->Value;
}
/**
\brief Atualiza o valor do atributo interpolavel
\param Value define o valor para o atributo interpolavel
*/
void AttrVector3::setValue(glm::vec3 Value)
{
	this->Value = Value;
}
/**
\brief Atualiza o respectivo parametro interpolavel de um determinado objeto Entity
\param ptrParent ponteiro para o objeto a ser atualizado
*/
void AttrVector3::updateParent(Entity * ptrParent)
{
	if (!ptrParent)
		return;

	switch (this->attrName)
	{
	case PoseAttr::TRANSLATE:		ptrParent->setTranslate(this->Value); ptrParent->setPhysicTranslate(this->Value); break;
	case PoseAttr::ADD_TRANSLATE:	ptrParent->setTranslate(this->Value); ptrParent->setPhysicTranslate(this->Value); break;
	case PoseAttr::ROTATE:			ptrParent->setRotate(this->Value);    break;
	case PoseAttr::ROTATE_PIVOT:	ptrParent->setRotatePivot(this->Value); break;
	case PoseAttr::SCALE:			ptrParent->setScale(this->Value);     break;
	}
}
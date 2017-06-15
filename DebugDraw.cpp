#include "stdafx.h"
#include "DebugDraw.h"

#include "Constants.h"
#include "Application.h"


DebugDraw::DebugDraw()
{
}


DebugDraw::~DebugDraw()
{
}

void DebugDraw::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	Application::p ponto;
	ponto.from = glm::vec3(from.getX(), from.getY(), from.getZ());
	ponto.to = glm::vec3(to.getX(), to.getY(), to.getZ());
	ptrApp->pontos.push_back(ponto);

}

void DebugDraw::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{

}

void DebugDraw::reportErrorWarning(const char* warningString)
{

}

void DebugDraw::draw3dText(const btVector3& location, const char* textString)
{

}

void DebugDraw::setDebugMode(int m_debugMode)
{
	this->m_debugMode = m_debugMode;
}

int DebugDraw::getDebugMode() const
{
	return m_debugMode;
}

void DebugDraw::doDrawing()
{
	//ptrApp->DebugDraw();

}

void DebugDraw::cleanDrawing()
{
}

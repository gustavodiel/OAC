#pragma once
#include <LinearMath/btIDebugDraw.h>
#include <vector>
#include <glm/glm.hpp>
#include <gl/glew.h>

class DebugDraw :
	public btIDebugDraw
{
private:
	int m_debugMode;
public:
	DebugDraw(void);
	virtual ~DebugDraw(void);




	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color);

	virtual void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color);

	virtual void reportErrorWarning(const char* warningString);

	virtual void draw3dText(const btVector3& location, const char* textString);

	virtual void setDebugMode(int m_debugMode);

	virtual int getDebugMode() const;

	void doDrawing();
	void cleanDrawing();
};

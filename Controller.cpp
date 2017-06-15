#include "stdafx.h"
#include "Controller.h"

#include "Constants.h"
#include "Application.h"
#include "Camera.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Utilities.hpp"


Controller::Controller()
{

}


Controller::~Controller()
{
}


void Controller::computeMatricesFromInputs(float deltaTime, glm::vec3* lookAt, glm::vec3* camPosition)
{
	glm::vec3 direction;

	if (lookAt) {
		direction = *lookAt;
		horizontalAngle = 3.1415f;
		verticalAngle = 0;
	}
	else {
		// Direction : Spherical coordinates to Cartesian coordinates conversion
		// Get mouse position
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		// Reset mouse position for next frame
		glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);

		// Compute new orientation
		horizontalAngle += mouseSpeed * float(windowWidth / 2 - xpos);
		verticalAngle += mouseSpeed * float(windowHeight / 2 - ypos);

		direction = {
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
		};
	}


	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f / 2.0f),
		0,
		cos(horizontalAngle - 3.14f / 2.0f)
	);
	glm::vec3 up;
	if (lookAt) {
		up = glm::vec3(0, 1, 0);
	}
	else {
		up = glm::cross(right, direction);
	}

	// Up vector
	

	if (camPosition) {
		position = *camPosition;
	}
	else {
		// Move forward
		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			position += direction * deltaTime * speed;
		}
		// Move backward
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			position -= direction * deltaTime * speed;
		}
		// Strafe right
		if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
			position += right * deltaTime * speed;
		}
		// Strafe left
		if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			position -= right * deltaTime * speed;
		}
	}
	
	float FoV = this->initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.
	
	glm::vec3 dir = position + direction;

	if (lookAt) {
		dir = *lookAt;
	}
	else {
		dir = position + direction;
	}
	/*
	if (ptrApp->ptrcMainCamera) {
		ptrApp->ptrcMainCamera->setTranslate(position);
		ptrApp->ptrcMainCamera->setRotate(dir - ptrApp->ptrcMainCamera->getTranslate());
	}*/

						   // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 16.0f / 9.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		//position + direction, // and looks here : at the same position, plus "direction"
		dir,
		up                  // Head is up (set to 0,-1,0 to look upside-down)
		);
}

glm::mat4 Controller::getViewMatrix()
{
	return ViewMatrix;
}

glm::mat4 Controller::getProjectionMatrix()
{
	return ProjectionMatrix;
}

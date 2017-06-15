#pragma once

#include <glm\glm.hpp>
class Controller
{
protected:
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;


public:
	Controller();
	~Controller();

	struct GLFWwindow* window;

	// Initial position : on +Z
	glm::vec3 position = glm::vec3(0, 0, 5);
	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 45.0f;

	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;


	int windowWidth;
	int windowHeight;

	void computeMatricesFromInputs(float deltaTime, glm::vec3* lookAt = NULL, glm::vec3* camPosition = NULL);
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();

};


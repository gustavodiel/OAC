#include "stdafx.h"
#include "Keyboard.h"

#include "Constants.h"
#include "Application.h"
#include "Model.h"
#include "Camera.h"


#include <GLFW\glfw3.h>
#include "Utilities.hpp"


Keyboard::Keyboard()
{
}


Keyboard::~Keyboard()
{
}

void Keyboard::OnProcessEvent() {
	if (glfwGetKey(ptrApp->GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS && !spacePressed) {
		spacePressed = true;
		char* nome;
		switch (this->letra)
		{
		case 0:
			nome = "objs/D.obj";
			break;
		case 1:
			nome = "objs/i.obj";
			break;
		case 2:
			nome = "objs/e.obj";
			break;
		case 3:
			nome = "objs/L.obj";
			break;
		default:
			nome = "objs/circle1cm.obj";
			break;
		}
		this->letra++;
		if (this->letra > 3)
			this->letra = 0;
		Model *cubo = new Model(nome, "textures/branco.jpg");
		cubo->setTranslate(ptrApp->ptrcMainCamera->getTranslate());
		ptrApp->AddEntity(cubo);

		cubo->setMass(1.0f);
		cubo->ActivatePhysics(Entity::BOX);

		cubo->ApplyForce(ptrApp->ptrcMainCamera->getRotate() * 10.0f);
	}
	if (glfwGetKey(ptrApp->GetWindow(), GLFW_KEY_SPACE) == GLFW_RELEASE && spacePressed) {
		spacePressed = false;
	}

	if (glfwGetMouseButton(ptrApp->GetWindow(), GLFW_MOUSE_BUTTON_1) == GLFW_PRESS && !mouseClicked) {
		mouseClicked = true;
		Model *cubo = new Model("objs/circle1cm.obj", "textures/branco.jpg");
		cubo->setScale(vec3(.2, .2, .2));
		cubo->setTranslate(ptrApp->ptrcMainCamera->getTranslate());
		ptrApp->AddEntity(cubo);

		cubo->setMass(1.0f);
		cubo->ActivatePhysics(Entity::SPHERE);

		cubo->ApplyForce(vec3(ptrApp->ptrcMainCamera->getRotate() * 10.0f));

	}
	if (glfwGetMouseButton(ptrApp->GetWindow(), GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE && mouseClicked) {
		mouseClicked = false;
	}

	if (glfwGetMouseButton(ptrApp->GetWindow(), GLFW_MOUSE_BUTTON_2) == GLFW_PRESS && !rightMouseClicked) {
		rightMouseClicked = true;
		Model *cubo = new Model("objs/ponies.obj", "textures/branco.jpg");
		cubo->setTranslate(ptrApp->ptrcMainCamera->getTranslate());
		ptrApp->AddEntity(cubo);

		cubo->setMass(1.0f);
		cubo->ActivatePhysics(Entity::BOX);

		cubo->ApplyForce(vec3(ptrApp->ptrcMainCamera->getRotate() * 10.0f));

	}
	if (glfwGetMouseButton(ptrApp->GetWindow(), GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE && rightMouseClicked) {
		rightMouseClicked = false;
	}

}
#pragma once
class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	void OnProcessEvent();

	int letra = 0;


	bool spacePressed = false;
	bool mouseClicked = false;
	bool rightMouseClicked = false;
};


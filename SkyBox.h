#pragma once
class SkyBox
{
public:
	SkyBox();
	~SkyBox();

	void Initialize();
	void OnRender();

private:
	unsigned int skyboxProgram;
	unsigned int skyboxVAO, skyboxVBO;
	unsigned int cubemapTexture;
};

 
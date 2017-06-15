#include "stdafx.h"
#include "Cloud.h"

#include "BillBoard.h"
#include <glm\gtx\transform.hpp>

Cloud::Cloud(const char* texture)
{
	bpCloud = new BillBoard(texture);
	bpCloud->SetShearable(false);
}


Cloud::~Cloud()
{
}

void Cloud::setTranslate(glm::vec3 vec) {
	bpCloud->setTranslate(vec);
}

void Cloud::OnLoop(double dDeltaTime)
{
	Actor2D::OnLoop(dDeltaTime);
	bpCloud->OnLoop(dDeltaTime);
}

void Cloud::LoadDimensions()
{
}

void Cloud::OnPreRender(glm::mat4 mat)
{
	bpCloud->OnPreRender(mat);
}

void Cloud::OnRender(glm::mat4 mat)
{

	bpCloud->OnRender(mat);
}

void Cloud::setSize(glm::vec2 size) {
	bpCloud->SetSize(size);
}

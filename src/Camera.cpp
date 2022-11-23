#include "Camera.h"



Camera::Camera()
{
}

Camera::~Camera()
{
}

Camera::Camera(int widthRes, int heightRes)
{
	this->eye = glm::vec3(0.0f, 0.0f, 7.0f);
	this->lookat = glm::vec3(0.0f, 0.0f, 0.0f);
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->FovY = 45;
	this->focalDistance = 1;
	this->widthRes = widthRes;
	this->heightRes = heightRes;
	renderedImage = new float[widthRes * heightRes * 3];
}

void Camera::TakePicture(Scene *scene)
{
	memset(renderedImage, 0, sizeof(float) * widthRes * heightRes * 3);
}

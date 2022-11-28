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

	//loop over all pixels and find the ray from camera to pixel
	glm::vec3 origin;
	std::vector<Light*> lights = scene->getLights();
	std::vector<Shape*> shapes = scene->getShapes();
	float focaldistance = sqrt(pow((lookat.x - eye.x), 2) + pow((lookat.y - eye.y), 2) + pow((lookat.z - eye.z), 2));
	for (int i = 0; i < heightRes; i++) {
		for (int j = 0; j < widthRes; j++) {

			//calculate primary ray
			
			float ly = 2 * focalDistance * tan((float) this->FovY / 2.0);
			float lx = ly * widthRes / heightRes;
			float Pw = ly / heightRes;


			origin = glm::normalize(lookat - eye) * (float) focalDistance;
			origin.x = origin.x - lx / 2.0 * j;
			origin.y = origin.y - ly / 2.0 * i;
			origin = origin + eye;

			//glm::vec3 Pc = origin
			//Pc = O + Pw(i + 0.5)*u + Pw(j + 0.5) * v;

			//Recursive function to return color of array
			//shape
			//light
			


			//renderedImage[j][i] = float color returned color of pixel

		}
	}

}

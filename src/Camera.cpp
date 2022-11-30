#include "Camera.h"
#include <iostream>

//struct Record {
//	glm::vec3 ka;
//	glm::vec3 ks;
//	glm::vec3 km;
//	glm::vec3 kd;
//	float n;
//	Record(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n) : ka(ka), kd(kd), ks(ks), km(km), n(n) {}
//};

Camera::Camera()
{
}

Camera::~Camera()
{
}

glm::vec3 Camera::ComputeRayColor(glm::vec3 origin, glm::vec3 ray, float t0, float t1, Scene* scene, int iter) {
	
	if (iter == 4) {
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
	
	std::vector<Shape*> rec;
	std::vector<Shape*> srec;
	glm::vec3 color(0.0f, 0.0f, 0.0f);
	float t = scene->hit(origin, ray, t0, t1, rec);
	if (t != FLT_MAX) { //ray has hit an object
		
		//color = ambient 
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		color = rec[0]->getKa();

		std::vector<Light*> lights = scene->getLights();
		glm::vec3 intersection = origin + t * ray;

		//shader phong

		glm::vec3 normal = glm::normalize(rec[0]->getNormal(intersection));
		glm::vec3 E = glm::normalize(this->eye - intersection);

		for (auto* light : lights) {

			glm::vec3 lightPosition = light->getPosition();
			glm::vec3 lightColor = light->getColor();
			//calculate shadow ray
			glm::vec3 shadowOrigin = intersection;
			glm::vec3 shadowRay = glm::normalize(lightPosition - intersection);
			if (scene->hit(shadowOrigin, shadowRay, 0.0001, glm::dot(lightPosition - shadowOrigin, shadowRay), srec) == FLT_MAX) {
				glm::vec3 L = glm::normalize(lightPosition - intersection);
				glm::vec3 R = glm::normalize(2 * (dot(L, normal)) * normal - L);
				color += lightColor * ((rec[0]->getKd() * std::max(0.0f, dot(L, normal))) + (rec[0]->getKs() * pow(std::max(0.0f, glm::dot(R, E)), rec[0]->getN())));
			}
		}
		//reflected ray
		glm::vec3 reflectedRay = ray - 2.0f * normal * glm::dot(ray, normal);
		return color + rec[0]->getKm() * ComputeRayColor(intersection, reflectedRay, 0.0001, FLT_MAX, scene, ++iter);
	}
	return color;

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

	glm::vec3 a = this->eye - this->lookat;
	glm::vec3 w = normalize(a);
	glm::vec3 u = glm::normalize(glm::cross(this->up, w));
	glm::vec3 v = glm::cross(w, u);
	//float colorbuff[heightRes][widthRes][3];

	for (int i = 0; i < this->heightRes; i++) {
		for (int j = 0; j < this->widthRes; j++) {

			//calculate primary ray
			
			float ly = 2 * this->focalDistance * tan((float) this->FovY / 2.0);
			float lx = ly * this->widthRes / this->heightRes;
			float Pw = ly / heightRes;


			origin = (glm::normalize(lookat - eye) * (float) this->focalDistance) - (lx/2.0f) * u - (ly/2.0f) * v + eye;

			//glm::vec3 Pc = origin
			//Pc = O + Pw(i + 0.5)*u + Pw(j + 0.5) * v;
			glm::vec3 Pc = origin + Pw * (j+0.5f) * u + Pw * (i + 0.5f) * v;

			float t0 = 0.0f;
			float t1 = FLT_MAX;

			glm::vec3 ray = glm::normalize(Pc - this->eye); //direction

			//ray = Pc - eye =direction
			//origin = eye or PC
			// origin gets changed to new intersection point
			// direction becomes reflection
			// shadow ray is direction towards light
			//t0 = Pc

			//plane normal is given
			//sphere reflection is ray - x

			//

			origin = eye;
			glm::vec3 color = ComputeRayColor(origin, ray, t0, t1, scene, 0);


			

			//renderedImage[i][j] = float color returned color of pixel
			renderedImage[i * widthRes * 3 + j * 3 + 0] = color.x;
			renderedImage[i * widthRes * 3 + j * 3 + 1] = color.y;
			renderedImage[i * widthRes * 3 + j * 3 + 2] = color.z;


		}
	}

}

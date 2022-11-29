#include "Plane.h"


//Plane::Plane()
//{
//}


Plane::Plane(glm::vec3 center, glm::vec3 normal, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n):
	Shape(ka, kd, ks, km, n), center(center), normal(normal)  {}

Plane::~Plane()
{
}

float Plane::intersect(glm::vec3 origin, glm::vec3 ray, float t0, float t1)
{
	/*float t = FLT_MAX;

	float epsilon = 0.00001f;
	float pointVal = glm::dot(this->normal, ray);
	if (abs(pointVal) > epsilon) {
		t = glm::dot((this->center - origin), this->normal / pointVal);
	}*/
	//float denom = glm::dot(ray, this->normal);
	
	float t = (glm::dot((this->center - origin), this->normal)) / glm::dot(ray, this->normal);

	if (t < t0 || t >t1) return FLT_MAX;
	else return t;


	//return FLT_MAX;
}

glm::vec3 Plane::getNormal(glm::vec3 intersection)
{
	return this->normal;
}


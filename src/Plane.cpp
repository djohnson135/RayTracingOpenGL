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
	return FLT_MAX;
}

void Plane::getNormal() {}


#include "Sphere.h"

//Sphere::Sphere()
//{
//}

Sphere::Sphere(glm::vec3 position, float radius, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n) : 
	
	Shape(ka, kd, ks, km, n), position(position), radius(radius) {}

Sphere::~Sphere()
{
}

glm::vec3 Sphere::intersect() {}

void Sphere::getNormal() {}
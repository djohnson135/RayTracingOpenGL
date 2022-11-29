#include "Shape.h"

//Shape::Shape(void)
//{
//}

Shape::Shape(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n): ka(ka), kd(kd), ks(ks), km(km), n(n) {}


glm::vec3 Shape::intersect(glm::vec3 origin, glm::vec3 ray, float t0, float t1) 
{
	return glm::vec3();
}
void Shape::getNormal(){}

Shape::~Shape(void)
{
}


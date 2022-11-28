#include "Shape.h"

//Shape::Shape(void)
//{
//}

Shape::Shape(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n): ka(ka), kd(kd), ks(ks), km(km), n(n) {}


void Shape::intersect(){}
void Shape::getNormal(){}

Shape::~Shape(void)
{
}


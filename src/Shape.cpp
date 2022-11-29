#include "Shape.h"

//Shape::Shape(void)
//{
//}

Shape::Shape(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n): ka(ka), kd(kd), ks(ks), km(km), n(n) {}


float Shape::intersect(glm::vec3 origin, glm::vec3 ray, float t0, float t1) 
{
	return FLT_MAX;
}
glm::vec3 Shape::getNormal(glm::vec3 intersection)
{
	return glm::vec3();
}

Shape::~Shape(void)
{
}

glm::vec3 Shape::getKa() {
	return this->ka;
}
glm::vec3 Shape::getKd() {
	return this->kd;
}
glm::vec3 Shape::getKs() {
	return this->ks;
}
glm::vec3 Shape::getKm() {
	return this->km;
}
float Shape::getN() {
	return this->n;
}


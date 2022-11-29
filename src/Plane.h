#pragma once
#include "Shape.h"
//#include <glm/glm.hpp>

class Plane :
	public Shape
{
public:
	//Plane();
	Plane(glm::vec3 center, glm::vec3 normal, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n);
	float intersect(glm::vec3 origin, glm::vec3 ray, float t0, float t1);
	void getNormal();
	~Plane();

private:
	glm::vec3 center;
	glm::vec3 normal;
};

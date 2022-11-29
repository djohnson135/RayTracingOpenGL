#pragma once
#include "Shape.h"
//#include <glm/glm.hpp>


class Sphere :
	public Shape
{
public:
	//Sphere();
	Sphere(glm::vec3 position, float radius, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n);
	glm::vec3 intersect(glm::vec3 origin, glm::vec3 ray, float t0, float t1);
	void getNormal();
	~Sphere();

private:
	glm::vec3 position;
	float radius;
};

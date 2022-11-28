#pragma once
#include "Shape.h"
//#include <glm/glm.hpp>


class Sphere :
	public Shape
{
public:
	//Sphere();
	Sphere(glm::vec3 position, float radius, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n);
	void intersect();
	void getNormal();
	~Sphere();

private:
	glm::vec3 position;
	float radius;
};

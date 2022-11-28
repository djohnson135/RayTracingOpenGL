#pragma once
#include "Shape.h"
//#include <glm/glm.hpp>

class Plane :
	public Shape
{
public:
	//Plane();
	Plane(glm::vec3 center, glm::vec3 normal, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n);
	glm::vec3 intersect();
	void getNormal();
	~Plane();

private:
	glm::vec3 center;
	glm::vec3 normal;
};

#pragma once
#include <glm/glm.hpp>

class Shape
{
public:
	//Shape(void);
	Shape(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n);
	~Shape(void);

private:
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	glm::vec3 km;
	float n;
};

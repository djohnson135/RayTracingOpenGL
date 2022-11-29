#pragma once
#include <glm/glm.hpp>

class Shape
{
public:
	//Shape(void);
	Shape(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n);
	virtual float intersect(glm::vec3 origin, glm::vec3 ray, float t0, float t1);
	virtual glm::vec3 getNormal(glm::vec3 intersection);
	~Shape(void);	

private:
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	glm::vec3 km;
	float n;
};

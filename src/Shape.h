#pragma once
#include <glm/glm.hpp>

class Shape
{
public:
	//Shape(void);
	Shape(glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n);
	virtual float intersect(glm::vec3 origin, glm::vec3 ray, float t0, float t1);
	virtual glm::vec3 getNormal(glm::vec3 origin, glm::vec3 ray, glm::vec3 intersection);
	glm::vec3 getKa();
	glm::vec3 getKd();
	glm::vec3 getKs();
	glm::vec3 getKm();
	float getN();
	~Shape(void);	

private:
	glm::vec3 ka;
	glm::vec3 kd;
	glm::vec3 ks;
	glm::vec3 km;
	float n;
};

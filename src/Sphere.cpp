#include "Sphere.h"
#include <iostream>
//Sphere::Sphere()
//{
//}

Sphere::Sphere(glm::vec3 position, float radius, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n) : 
	
	Shape(ka, kd, ks, km, n), position(position), radius(radius) {}

Sphere::~Sphere()
{
}

float Sphere::intersect(glm::vec3 origin, glm::vec3 ray, float t0, float t1)
{

	float aq = dot(ray, ray);
	float bq = dot(ray * 2.0f, origin - this->position);
	float cq = dot(origin - this->position, origin - this->position) - pow(this->radius,2);


	float sqrtDeterminant = pow(bq, 2) - 4 * aq * cq;

	
	if (sqrtDeterminant < 0) return -1; //no intersection; //no solution
	
	float tpos = (-bq + sqrt(sqrtDeterminant)) / (2 * aq);
	float tneg = (-bq - sqrt(sqrtDeterminant)) / (2 * aq);



	if (tpos > t0 && tpos < t1 && tneg > t0 && tneg < t1) {
		//both are valid
		return std::min(tpos, tneg);
		
	}
	//if just tpos is valid
	if (tpos > t0 && tpos < t1 && (tneg < t0 || tneg > t1)) {
		return tpos;
	}

	//if just tneg is valid
	if (tneg > t0 && tneg < t1 && (tpos < t0 || tpos > t1)) {
		return tneg;
	}

	return -1;
	
}

glm::vec3 Sphere::getNormal(glm::vec3 origin, glm::vec3 ray, glm::vec3 intersection)
{
	//normalize (P-C)
	return glm::normalize(intersection - this->position);
}
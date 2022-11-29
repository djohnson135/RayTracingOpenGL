#include "Sphere.h"

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

	//return glm::vec3();
	//t = (-bq +/- sqrt(bq^2 - 4aq*cq)) / 2aq

	float aq = dot(ray, ray);
	float bq = dot(ray * 2.0f, origin - this->position);
	float cq = dot(origin - this->position, origin - this->position) - pow(this->radius,2);

	//quadratic formula
	//check if pow(bq, 2) - 4 * aq * cq) is negative
	float sqrtDeterminant = pow(bq, 2) - 4 * aq * cq;
	float tval;
	if (sqrtDeterminant < 0) return FLT_MAX; //no intersection; //no solution

	else if (sqrtDeterminant == 0) {
		float tpos = (-bq + sqrt(sqrtDeterminant)) / (2 * aq);

		float tneg = (-bq - sqrt(sqrtDeterminant)) / (2 * aq);

		if (tpos < t0 || tpos > t1) {
			return FLT_MAX; //no intersection
		}
		tval = tpos;
	}
	else {
		float tpos = (-bq + sqrt(sqrtDeterminant)) / (2 * aq);

		float tneg = (-bq - sqrt(sqrtDeterminant)) / (2 * aq);
		
		if (tpos < 0 && tneg < 0) {
			return FLT_MAX; //no intersection;
		}
		else if (tpos < 0) {
			tval = tneg;
		}
		else if (tneg < 0) {
			tval = tpos;
		}
		else {
			//find min of tpos and tneg
			if (tpos < tneg) {
				tval = tneg;
			}
			else {
				tval = tpos;
			}
		}
	}

	

	//2 cases
	
	//check if t >t0 and return smallest t
	//glm::vec3 intersection = origin + tval * ray;

	return tval;

}

glm::vec3 Sphere::getNormal(glm::vec3 intersection)
{
	//normalize (P-C)
	return glm::normalize(intersection - this->position);
}
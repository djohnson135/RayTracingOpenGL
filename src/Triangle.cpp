#include "Triangle.h"



Triangle::Triangle(glm::vec3& v0, glm::vec3& v1, glm::vec3& v2, glm::vec3& n0, glm::vec3& n1, glm::vec3& n2, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n) : Shape(ka, kd, ks, km, n)
{
	v[0] = v0;
	v[1] = v1;
	v[2] = v2;

	this->n[0] = n0;
	this->n[1] = n1;
	this->n[2] = n2;

};



Baycentric Triangle::baycentricCoordinate(float xPos, float yPos, glm::vec3 A, glm::vec3 B, glm::vec3 C) {

	float alpha = (-1 * ((xPos - B.x) * (C.y - B.y)) + (yPos - B.y) * (C.x - B.x)) /
		(-1 * ((A.x - B.x) * (C.y - B.y)) + (A.y - B.y) * (C.x - B.x));

	float beta = (-1 * ((xPos - C.x) * (A.y - C.y)) + (yPos - C.y) * (A.x - C.x)) /
		(-1 * ((B.x - C.x) * (A.y - C.y)) + (B.y - C.y) * (A.x - C.x));

	float gamma = 1 - alpha - beta;

	return Baycentric(alpha, beta, gamma);
}


float Triangle::intersect(glm::vec3 origin, glm::vec3 ray, float t0, float t1) {
	
	glm::vec3 v0v1 = this->v[1] - this->v[0];
	glm::vec3 v0v2 = this->v[2] - -this->v[0];
	glm::vec3 point = glm::cross(ray, v0v2);
	float det = glm::dot(v0v1, point);

	if (det < t0) {
		return -1;
	}
	float invDet = 1 / det;
	glm::vec3 tvec = origin - v[0];
	float u = glm::dot(tvec, point) * invDet;

	if (u < 0 || u > 1) return -1;
	glm::vec3 qvec = glm::cross(tvec, v0v1);
	float v = glm::dot(ray, qvec) * invDet;
	if (v < 0 || u + v >1) return -1;

	float t = glm::dot(v0v2, qvec) * invDet;
	return t;

	//b1 b2 1-b1-b2
}

glm::vec3 Triangle::getNormal(glm::vec3 intersection) {
	Baycentric bay = this->baycentricCoordinate(intersection.x, intersection.y, this->v[0], this->v[1], this->v[2]);
	return glm::vec3(0.0f, 0.0f, 0.0f);

	//normalize(alphaN1 + betaN2 + gammaN3)
	//including 0 and 1
	//B1 is beta B2 is gamma
}
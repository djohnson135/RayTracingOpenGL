#include "Triangle.h"
#include <iostream>


Triangle::Triangle(glm::vec3& v0, glm::vec3& v1, glm::vec3& v2, glm::vec3& n0, glm::vec3& n1, glm::vec3& n2, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n) : Shape(ka, kd, ks, km, n)
{
	v[0] = v0;
	v[1] = v1;
	v[2] = v2;

	this->n[0] = n0;
	this->n[1] = n1;
	this->n[2] = n2;

};

float Triangle::minX() {
	float z0 = v[0].x;
	float z1 = v[1].x;
	float z2 = v[2].x;

	if (z0 < z1 && z0 < z2) return z0;
	else if (z1 < z2) return z1;
	else return z2;
}

float Triangle::minY() {
	float z0 = v[0].y;
	float z1 = v[1].y;
	float z2 = v[2].y;

	if (z0 < z1 && z0 < z2) return z0;
	else if (z1 < z2) return z1;
	else return z2;
}

float Triangle::minZ() {
	float z0 = v[0].z;
	float z1 = v[1].z;
	float z2 = v[2].z;

	if (z0 < z1 && z0 < z2) return z0;
	else if (z1 < z2) return z1;
	else return z2;
}

float Triangle::maxX() {
	float z0 = v[0].x;
	float z1 = v[1].x;
	float z2 = v[2].x;

	if (z0 > z1 && z0 > z2) return z0;
	else if (z1 > z2) return z1;
	else return z2;
}

float Triangle::maxY() {
	float z0 = v[0].y;
	float z1 = v[1].y;
	float z2 = v[2].y;

	if (z0 > z1 && z0 > z2) return z0;
	else if (z1 > z2) return z1;
	else return z2;

}

float Triangle::maxZ() {
	float z0 = v[0].z;
	float z1 = v[1].z;
	float z2 = v[2].z;

	if (z0 > z1 && z0 > z2) return z0;
	else if (z1 > z2) return z1;
	else return z2;

}

Baycentric Triangle::baycentricCoordinate(float xPos, float yPos, glm::vec3 A, glm::vec3 B, glm::vec3 C) {

	float alpha = (-1 * ((xPos - B.x) * (C.y - B.y)) + (yPos - B.y) * (C.x - B.x)) /
		(-1 * ((A.x - B.x) * (C.y - B.y)) + (A.y - B.y) * (C.x - B.x));

	float beta = (-1 * ((xPos - C.x) * (A.y - C.y)) + (yPos - C.y) * (A.x - C.x)) /
		(-1 * ((B.x - C.x) * (A.y - C.y)) + (B.y - C.y) * (A.x - C.x));

	float gamma = 1 - alpha - beta;

	return Baycentric(alpha, beta, gamma);
}


float Triangle::intersect(glm::vec3 origin, glm::vec3 ray, float t0, float t1) {
	
	
	
	glm::vec3 E1 = this->v[1] - this->v[0];
	glm::vec3 E2 = this->v[2] - this->v[0];
	
	glm::vec3 S = origin - v[0];
	glm::vec3 S1 = glm::cross(ray, E2);
	glm::vec3 S2 = glm::cross(S, E1);
	
	float det = 1 / glm::dot(S1, E1);

	float t = det * glm::dot(S2, E2);
	if (t < t0 || t > t1) return -1;
	return t;

	//b1 b2 1-b1-b2
}

glm::vec3 Triangle::getNormal(glm::vec3 origin, glm::vec3 ray, glm::vec3 intersection) {
	//Baycentric bay = this->baycentricCoordinate(intersection.x, intersection.y, this->v[0], this->v[1], this->v[2]);
	
	
	glm::vec3 E1 = this->v[1] - this->v[0];
	glm::vec3 E2 = this->v[2] - this->v[0];

	glm::vec3 S = origin - v[0];
	glm::vec3 S1 = glm::cross(ray, E2);
	glm::vec3 S2 = glm::cross(S, E1);

	float det = 1 / glm::dot(S1, E1);

	float b1 = det * glm::dot(S1, S);
	float b2 = det * glm::dot(S2, ray);
	float b0 = 1 - b1 - b2;
	
	
	
	
	
	
	
	
	
	
	/*glm::vec3 v0v1 = this->v[1] - this->v[0];
	glm::vec3 v0v2 = this->v[2] - -this->v[0];
	glm::vec3 point = glm::cross(ray, v0v2);
	float det = glm::dot(v0v1, point);

	float invDet = 1 / det;
	glm::vec3 tvec = origin - v[0];
	float b1 = glm::dot(tvec, point) * invDet;

	glm::vec3 qvec = glm::cross(tvec, v0v1);
	float b2 = glm::dot(ray, qvec) * invDet;*/
	

	//normalize(alphaN1 + betaN2 + gammaN3)
	//including 0 and 1
	//B1 is beta B2 is gamma
	//glm::normalize()

	glm::vec3 normal = this->n[0] * b0 + this->n[1] * b1 + this->n[2] * b2;
	return glm::normalize(normal);
}
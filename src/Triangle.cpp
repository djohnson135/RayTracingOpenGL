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
	
	float det = glm::dot(S1, E1);

	if (det < t0) return -1;

	float invDet = 1 / det;

	float b1 = invDet * glm::dot(S1, S); 
	if (b1 < 0 || b1 > 1) return -1;

	float b2 = invDet * glm::dot(S2, ray);
	if (b2 < 0 || b2 + b1 > 1) return -1;

	float b0 = 1 - b1 - b2;

	float t = invDet * glm::dot(S2, E2);


	if (t < t0 || t > t1) return -1;
	this->b0 = b0;
	this->b1 = b1;
	this->b2 = b2;

	return t;

	//b1 b2 1-b1-b2
}

glm::vec3 Triangle::getNormal(glm::vec3 origin, glm::vec3 ray, glm::vec3 intersection) {
	//Baycentric bay = this->baycentricCoordinate(intersection.x, intersection.y, this->v[0], this->v[1], this->v[2]);

	glm::vec3 normal = this->n[0] * this->b0 + this->n[1] * this->b1 + this->n[2] * this->b2;
	return glm::normalize(normal);
}


float Triangle::averageX() {
	return (this->v[0].x + this->v[1].x + this->v[2].x) / 3.0;
}
float Triangle::averageY() {
	return (this->v[0].y + this->v[1].y + this->v[2].y) / 3.0;

}
float Triangle::averageZ() {
	return (this->v[0].z + this->v[1].z + this->v[2].z) / 3.0;

}
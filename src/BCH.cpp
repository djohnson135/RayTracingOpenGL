#include "BCH.h"
#include "Triangle.h"
#include <iostream>
BCH::BCH(std::vector<Triangle*> triangles, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n) : Shape(ka, kd, ks, km, n)

{
	float minXV = FLT_MAX;
	float minYV = FLT_MAX;
	float minZV = FLT_MAX;

	float maxXV = 0.0f;
	float maxYV = 0.0f;
	float maxZV = 0.0f;
	for (auto* triangle : triangles) {
		//Triangle* t = triangle;
		if (triangle->minX() < minXV) minXV = triangle->minX();
		if (triangle->minY() < minYV) minYV = triangle->minY();
		if (triangle->minZ() < minZV) minZV = triangle->minZ();

		if (triangle->maxX() > maxXV) maxXV = triangle->maxX();
		if (triangle->maxY() > maxYV) maxYV = triangle->maxY();
		if (triangle->maxZ() > maxZV) maxZV = triangle->maxZ();
		this->triangles.push_back(triangle);
	}
	this->minX = minXV;
	this->minY = minYV;
	this->minZ = minZV;
	this->maxX = maxXV;
	this->maxY = maxYV;
	this->maxZ = maxZV;
	//this->intersectedTriangle = new Triangle();
}


float BCH::intersect(glm::vec3 origin, glm::vec3 ray, float t0, float t1) {


	float txmin = std::min((this->minX - origin.x) / ray.x, (this->maxX - origin.x) / ray.x);
	float txmax = std::max((this->minX - origin.x) / ray.x, (this->maxX - origin.x) / ray.x);

	float tymin = std::min((this->minY - origin.y) / ray.y, (this->maxY - origin.y) / ray.y);
	float tymax = std::max((this->minY - origin.y) / ray.y, (this->maxY - origin.y) / ray.y);

	float tzmin = std::min((this->minZ - origin.z) / ray.z, (this->maxZ - origin.z) / ray.z);
	float tzmax = std::max((this->minZ - origin.z) / ray.z, (this->maxZ - origin.z) / ray.z);


	float tmin;
	float tmax;

	//find the max min value
	if (txmin > tymin && txmin > tzmin) tmin = txmin;
	else if (tymin > tzmin) tmin = tymin;
	else tmin = tzmin;

	//find the min max value
	if (txmax < tymax && txmax < tzmax) tmax = txmax;
	else if (tymax < tzmax) tmax = tymax;
	else tmax = tzmax;

	//check if intersects
	if (tmin > tmax) return -1; //ray does not hit box

	float smallestIntersect = FLT_MAX;
	for (auto* triangle : this->triangles) {
		float newt = triangle->intersect(origin, ray, t0, t1);
		if (newt > t0 && newt < t1 && newt < smallestIntersect) {
			smallestIntersect = newt;
			this->intersectedTriangle = triangle;
		}
	}
	return smallestIntersect;
	
}
glm::vec3 BCH::getNormal(glm::vec3 origin, glm::vec3 ray, glm::vec3 intersection) {
	

	return this->intersectedTriangle->getNormal(origin, ray, intersection);
}


void BCH::computeBoundingBox() {
	
};
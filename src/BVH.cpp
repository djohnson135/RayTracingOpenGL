#include "BVH.h"
#include "Triangle.h"
#include <iostream>



BVH::BVH(std::vector<Triangle*> triangles, std::vector<TriangleBVH> triangleLoc, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n) : Shape(ka, kd, ks, km, n)

{
	//this->intersectedTriangle = new Triangle();
	this->trianglesInChildClass = triangles;
	computeBoundingBox(triangles, triangleLoc);
	this->triangleLoc = triangleLoc;
	this->left = nullptr;
	this->right = nullptr;
	this->intersectedTriangle = triangles[0];
}


float BVH::intersect(glm::vec3 origin, glm::vec3 ray, float t0, float t1) {


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
	if (tmin > tmax) {//ray does not hit box

		return -1; 
	}
	

	float smallestIntersect = FLT_MAX;
	if (this->left == nullptr || this->right == nullptr) {
		
		for (auto triangle : this->triangleLoc) {
			int index = triangle.location;
			float newt = this->trianglesInChildClass[index]->intersect(origin, ray, t0, t1);
			if (newt > t0 && newt < t1 && newt < smallestIntersect) {
				smallestIntersect = newt;
				this->intersectedTriangle = this->trianglesInChildClass[index];
			}
		}
		return smallestIntersect;

	}
	else {

		float leftTval = this->left->intersect(origin, ray, t0, t1);
		float rightTval = this->right->intersect(origin, ray, t0, t1);
		if (leftTval > t0 && rightTval > t0) {
			return std::min(leftTval, rightTval);
		}
		else if (leftTval > t0) {
			return leftTval;
		}
		else if (rightTval > t0) {
			return rightTval;
		}
		else return -1;
	}
	return -1;
}
glm::vec3 BVH::getNormal(glm::vec3 origin, glm::vec3 ray, glm::vec3 intersection) {


	return this->intersectedTriangle->getNormal(origin, ray, intersection);
}


void BVH::computeBoundingBox(std::vector<Triangle*> triangles, std::vector<TriangleBVH> triangleLoc) {
	float minXV = FLT_MAX;
	float minYV = FLT_MAX;
	float minZV = FLT_MAX;

	float maxXV = FLT_MIN;
	float maxYV = FLT_MIN;
	float maxZV = FLT_MIN;
	int iter = 0;
	for (auto triangle : triangleLoc) {
		//Triangle* t = triangle;
		iter = triangle.location;

		if (triangles[iter]->minX() < minXV) minXV = triangles[iter]->minX();
		if (triangles[iter]->minY() < minYV) minYV = triangles[iter]->minY();
		if (triangles[iter]->minZ() < minZV) minZV = triangles[iter]->minZ();

		if (triangles[iter]->maxX() > maxXV) maxXV = triangles[iter]->maxX();
		if (triangles[iter]->maxY() > maxYV) maxYV = triangles[iter]->maxY();
		if (triangles[iter]->maxZ() > maxZV) maxZV = triangles[iter]->maxZ();
		this->triangles.push_back(triangles[iter]);
	}
	this->minX = minXV;
	this->minY = minYV;
	this->minZ = minZV;
	this->maxX = maxXV;
	this->maxY = maxYV;
	this->maxZ = maxZV;
};

void BVH::sortTriangles() {

}

bool BVH::isIntersected(glm::vec3 origin, glm::vec3 ray, float t0, float t1) {
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
	if (tmin > tmax) {//ray does not hit box

		return false;
	}
	return true;

}
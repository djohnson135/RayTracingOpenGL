#include "BCH.h"
#include "Triangle.h"

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

}


float BCH::intersect(glm::vec3 origin, glm::vec3 ray, float t0, float t1) {
	//return -1;
	//6 planes
	//float t = (glm::dot((this->center - origin), this->normal)) / glm::dot(ray, this->normal);
	/*float tminX = (this->minX - origin)*/
	/*glm::vec3 p0 = glm::vec3(this->minX, this->minY, this->maxZ);
	glm::vec3 p1 = glm::vec3(this->minX, this->maxY, this->minZ);
	glm::vec3 p2 = glm::vec3(this->minX, this->maxY, this->maxZ);
	glm::vec3 p3 = glm::vec3(this->maxX, this->minY, this->minZ);
	glm::vec3 p4 = glm::vec3(this->maxX, this->minY, this->maxZ);
	glm::vec3 p5 = glm::vec3(this->maxX, this->maxY, this->minZ);

	float txMin = (p0 - origin) / ray;*/

	//float txmin = (this->minX - origin.x) / ray.x;
	//float txmax = (this->maxX - origin.x) / ray.x;

	//float tymin = (this->minY - origin.y) / ray.y;
	//float tymax = (this->maxY - origin.y) / ray.y;

	//float tzmin = (this->minZ - origin.z) / ray.z;
	//float tzmax = (this->maxZ - origin.z) / ray.z;

	//float tmin;
	//float tmax;

	//if (txmin > tymin && txmin > tzmin) tmin = txmin;
	//else if (tymin > tzmin) tmin = tymin;
	//else tmin = tzmin;

	//if (txmax > tymax && txmax > tzmax) tmax = txmax;
	//else if (tymax > tzmax) tmax = tymax;
	//else tmax = tzmax;

	//if (tmin > tmax || tmax < 0) return -1; //ray does not hit box

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
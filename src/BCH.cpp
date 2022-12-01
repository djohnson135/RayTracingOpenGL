#include "BCH.h"


BCH::BCH(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, std::vector<Shape*> triangles, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n) :
	minX(minX), minY(minY), minZ(minZ), maxX(maxX), maxY(maxY), maxZ(maxZ), triangles(triangles), Shape(ka, kd, ks, km, n)

{}


float BCH::intersect(glm::vec3 origin, glm::vec3 ray, float t0, float t1) {
	return -1;
}
glm::vec3 BCH::getNormal(glm::vec3 origin, glm::vec3 ray, glm::vec3 intersection) {
	return glm::vec3(0.0f, 0.0f, 0.0f);
}


void BCH::computeBoundingBox() {
	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float minZ = FLT_MAX;

	float maxX = 0.0f;
	float maxY = 0.0f;
	float maxZ = 0.0f;
	for (auto* triangle : this->triangles) {
		/*if (triangle->minX() < minX) minX = triangle->minX();
		if (triangle->minY() < minY) minY = triangle->minY();
		if (triangle->minZ() < minZ) minZ = triangle->minZ();

		if (triangle->maxX() > maxX) maxX = triangle->maxX();
		if (triangle->maxY() > maxY) maxY = triangle->maxY();
		if (triangle->maxZ() > maxZ) maxZ = triangle->maxZ();*/
	}
};
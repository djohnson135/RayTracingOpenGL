#include "BCH.h"


BCH::BCH(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, std::vector<Shape*> triangles, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n) :
	minX(minX), minY(minY), minZ(minZ), maxX(maxX), maxY(maxY), maxZ(maxZ), triangles(triangles), Shape(ka, kd, ks, km, n)

{}
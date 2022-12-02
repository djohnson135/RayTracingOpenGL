#pragma once
#include "Shape.h"
#include <vector>
#include "Triangle.h"
class BVH :
	public Shape
{
public:
	BVH(std::vector<Triangle*> triangles, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n);
	float intersect(glm::vec3 origin, glm::vec3 ray, float t0, float t1);
	glm::vec3 getNormal(glm::vec3 origin, glm::vec3 ray, glm::vec3 intersection);
	void computeBoundingBox();
	void sortTriangles();
private:
	std::vector<Shape*> triangles;

	float minX;
	float minY;
	float minZ;
	float maxX;
	float maxY;
	float maxZ;
	Shape* intersectedTriangle;

};
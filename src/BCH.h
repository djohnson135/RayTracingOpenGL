#pragma once
#include "Shape.h"
#include <vector>

class BCH :
	public Shape
{
	BCH(float minX, float minY, float minZ, float maxX, float maxY, float maxZ, std::vector<Shape*> triangles, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n);

private:
	std::vector<Shape*> triangles;

	float minX;
	float minY;
	float minZ;
	float maxX;
	float maxY;
	float maxZ;

};
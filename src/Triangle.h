#pragma once
#include "Shape.h"


struct Baycentric {
	float alpha = -1;
	float beta = -1;
	float gamma = -1;
	Baycentric(float alpha, float beta, float gamma) : alpha(alpha), beta(beta), gamma(gamma) {};
	bool Inside() {
		if (this->alpha >= 0 && this->alpha <= 1) {
			if (this->beta >= 0 && this->beta <= 1) {
				if (this->gamma >= 0 && this->gamma <= 1) return true;
			}
		}
		return false;
	}
};

struct BoundingBox {
	int minY, maxY, minX, maxX = 0;

	BoundingBox(int minY, int maxY, int minX, int maxX) {
		this->minY = minY;
		this->maxY = maxY;
		this->minX = minX;
		this->maxX = maxX;
	}
};


class Triangle :
	public Shape
{


public:
	Triangle(glm::vec3& v0, glm::vec3& v1, glm::vec3& v2, glm::vec3& n0, glm::vec3& n1, glm::vec3& n2, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n);
	Baycentric baycentricCoordinate(float xPos, float yPos, glm::vec3 A, glm::vec3 B, glm::vec3 C);
	float intersect(glm::vec3 origin, glm::vec3 ray, float t0, float t1);
	glm::vec3 getNormal(glm::vec3 origin, glm::vec3 ray, glm::vec3 intersection);
	/*float minX();
	float minY();
	float minZ();

	float maxX();
	float maxY();
	float maxZ();*/

private:
	glm::vec3 v[3];		// Triangle vertices
	glm::vec3 n[3];     //triangle normals
};
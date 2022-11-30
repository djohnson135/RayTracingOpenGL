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


class Triangle {


public:
	Triangle();
	Triangle(glm::vec3& v0, glm::vec3& v1, glm::vec3& v2);


private:
	glm::vec3 v[3];		// Triangle vertices
};
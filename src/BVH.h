#pragma once
#include "Shape.h"
#include <vector>
#include "Triangle.h"

struct TriangleBVH {
	int location;
	float averageX;
	float averageY;
	float averageZ;
	TriangleBVH(int location, float averageX, float averageY, float averageZ) : location(location), averageX(averageX), averageY(averageY), averageZ(averageZ) {}
};



class BVH :
	public Shape
{
public:
	BVH(std::vector<Triangle*> triangles, std::vector<TriangleBVH> triangleLoc, glm::vec3 ka, glm::vec3 kd, glm::vec3 ks, glm::vec3 km, float n);
	float intersect(glm::vec3 origin, glm::vec3 ray, float t0, float t1);
	bool isIntersected(glm::vec3 origin, glm::vec3 ray, float t0, float t1);
	glm::vec3 getNormal(glm::vec3 origin, glm::vec3 ray, glm::vec3 intersection);
	void computeBoundingBox(std::vector<Triangle*> triangles, std::vector<TriangleBVH> triangleLoc);
	void sortTriangles();
	BVH* right;
	BVH* left;
private:
	std::vector<Shape*> triangles;
	std::vector<Triangle*> trianglesInChildClass;

	std::vector<TriangleBVH> triangleLoc;
	
	float minX;
	float minY;
	float minZ;
	float maxX;
	float maxY;
	float maxZ;
	Shape* intersectedTriangle;


};


struct node {
	node() { this->left = nullptr; this->right = nullptr; depth = 0; }
	BVH* left;
	BVH* right;
	int depth;
};
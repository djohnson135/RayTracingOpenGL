#pragma once
#include <vector>
#include "Shape.h"
#include "Light.h"
#include "BCH.h"
#include "BVH.h"
//#include <glm/glm.hpp>

class Scene
{
public:
	Scene();
	~Scene();
	Scene(BCH* box);
	Scene(BVH* box);

	Scene(std::vector<Shape*>);

	float hit(glm::vec3 origin, glm::vec3 ray, float t0, float t1, std::vector<Shape*>& rec);
	std::vector<Light*> getLights() { return this->lights; }
	std::vector<Shape*> getShapes() { return this->shapes; }


private:
	std::vector<Shape*> shapes;
	std::vector<Light*> lights;

};

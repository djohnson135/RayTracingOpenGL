#pragma once
#include <vector>
#include "Shape.h"
#include "Light.h"

//#include <glm/glm.hpp>

class Scene
{
public:
	Scene();
	~Scene();
	std::vector<Light*> getLights() { return this->lights; }
	std::vector<Shape*> getShapes() { return this->shapes; }


private:
	std::vector<Shape*> shapes;
	std::vector<Light*> lights;

};

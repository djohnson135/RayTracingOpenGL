#pragma once
#include <vector>
#include "Scene.h"
#include <glm/glm.hpp>
//#include <limits>
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <iostream>
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <vector>
//#include <algorithm>


class Camera
{
public:
	Camera();
	~Camera();

	Camera(int widthRes, int heightRes);

	void TakePicture(Scene *scene);
	float* GetRenderedImage() { return renderedImage; };
	glm::vec3 ComputeRayColor(glm::vec3 origin, glm::vec3 ray, float t0, float t1, Scene* scene);

private:

	glm::vec3 eye;
	glm::vec3 lookat;
	glm::vec3 up;
	int FovY;
	int focalDistance;
	int widthRes;
	int heightRes;
	float *renderedImage;
};

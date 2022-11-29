#pragma once
#include <glm/glm.hpp>

class Light
{
public:
	//Light();
	Light(glm::vec3 position, glm::vec3 color);

	~Light();
	glm::vec3 getPosition();
	glm::vec3 getColor();

private:
	glm::vec3 position;
	glm::vec3 color;
};

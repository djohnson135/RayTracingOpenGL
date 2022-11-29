#include "Light.h"

//Light::Light(void)
//{
//}

Light::Light(glm::vec3 position, glm::vec3 color) : position(position), color(color) {}


Light::~Light(void)
{
}

glm::vec3 Light::getPosition() {
	return this->position;
}


glm::vec3 Light::getColor() {
	return this->color;
}
#include "Triangle.h"

Triangle::Triangle()
{
	v[0] = glm::vec3(0.0f, 0.0f, 0.0f);
	v[1] = glm::vec3(0.0f, 0.0f, 0.0f);
	v[2] = glm::vec3(0.0f, 0.0f, 0.0f);
}


Triangle::Triangle(glm::vec3& v0, glm::vec3& v1, glm::vec3& v2)
{
	v[0] = v0;
	v[1] = v1;
	v[2] = v2;
};
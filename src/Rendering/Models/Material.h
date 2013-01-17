#ifndef MATERIAL_POWER_PONG_H
#define MATERIAL_POWER_PONG_H

#include <glm\glm.hpp>

struct Material
{
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 ambient;
	float shininess;
};

#endif
#ifndef LIGHT_H
#define LIGHT_H
#include <glm\glm.hpp>

struct Light
{
	Light();
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::vec4 ambient;
	
	
};

struct DirectionalLight:public Light
{
	glm::vec4  direction;
	glm::vec4 transformedDirection;

};
#endif
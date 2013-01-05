#ifndef LIGHT_H
#define LIGHT_H
#include <glm\glm.hpp>

struct Light
{
	Light();
	glm::vec3 color;
	float diffuseIntensity;
	
};

struct DirectionalLight:public Light
{
	glm::vec3  direction;

};
#endif
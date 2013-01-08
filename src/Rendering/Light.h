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

struct PointLight:public Light{
	glm::vec4 position;
	glm::vec4 transformedPosition;

	float constantAttenuation;
	float linearAttenutation;
	float quadraticAttenuation;



};
struct DirectionalLight:public Light
{
	glm::vec4  direction;
	glm::vec4 transformedDirection;

};
#endif
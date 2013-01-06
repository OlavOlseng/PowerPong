#ifndef pipeline_h
#define pipeline_h
#include <glm/glm.hpp>
#include "Shader.h"
#include <hash_map>
#include "Light.h"
class Pipeline
{
public:
	Pipeline(unsigned int maxDirectionalLights);
	~Pipeline(void);
	void setView(glm::mat4  view);
	glm::mat4 getView();
	void setProjection(glm::mat4  projection);
	glm::mat4 getProjection();
	void useShader(int id);
	void setViewDirection(glm::vec4 direction);
	glm::vec4 getViewDirection();

	Shader*getActiveShader();
	void addShader(Shader*shader,int id);
	glm::mat4 getTotalRotationTranslation();
	void setTotalRotationTranslation(glm::mat4 value);
	
	unsigned int getNumDirectionalLights();
	void addDirectionalLight(DirectionalLight * light);
	void popDirectionalLight(unsigned int pops = 1);
	DirectionalLight*getDirectionalLight(unsigned int index);
	void clear();
	
private:
	Shader*activeShader;
	glm::mat4 totalRotationTranslation;
	glm::mat4 view;
	glm::mat4 projection;
	glm::vec4 viewDirection;
	std::vector<Shader*> shaders;
	DirectionalLight **directionalLights;
	unsigned int numDirectionalLights;
	
};

#endif
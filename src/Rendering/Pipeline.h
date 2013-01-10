#ifndef pipeline_h
#define pipeline_h
#include <glm/glm.hpp>
#include "Shader.h"
#include <hash_map>
#include "Light.h"
class Pipeline
{
public:
	Pipeline(unsigned int maxDirectionalLights = 10,unsigned int maxPointLights = 10);
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
	
	void addLight(DirectionalLight*light);
	void addLight(PointLight * light);

	unsigned int getNumDirectionalLights();
	
	void popDirectionalLight(unsigned int pops = 1);
	DirectionalLight*getDirectionalLight(unsigned int index);

	unsigned int getNumPointLights();

	void popPointlLight(unsigned int pops = 1);
	PointLight*getPointLight(unsigned int index);

	void setShadowPass(bool shadowPass);
	bool isShadowPass();

	void clear();
	
private:
	Shader*activeShader;
	glm::mat4 totalRotationTranslation;
	glm::mat4 view;
	glm::mat4 projection;
	glm::vec4 viewDirection;
	std::vector<Shader*> shaders;
	DirectionalLight **directionalLights;
	PointLight**pointLights;
	unsigned int numDirectionalLights;
	unsigned int numPointLights;
	unsigned int maxDirectionalLights,maxPointLights;
	bool shadowPass;
};

#endif
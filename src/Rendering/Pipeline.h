#ifndef pipeline_h
#define pipeline_h
#include <glm/glm.hpp>
#include "Shader.h"
#include <hash_map>
class Pipeline
{
public:
	Pipeline(void);
	~Pipeline(void);
	void setView(glm::mat4  view);
	glm::mat4 getView();
	void setProjection(glm::mat4  projection);
	glm::mat4 getProjection();
	void useShader(std::string name);
	Shader*getActiveShader();
	void addShader(Shader*shader,std::string id);

private:
	Shader*activeShader;
	glm::mat4 view;
	glm::mat4 projection;
	std::hash_map<std::string,Shader*> shaders;

};

#endif
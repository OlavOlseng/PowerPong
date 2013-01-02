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
	void useShader(int id);
	Shader*getActiveShader();
	void addShader(Shader*shader,int id);
	glm::mat4 getTotalRotationTranslation();
	void setTotalRotationTranslation(glm::mat4 value);

	void clear();
	
private:
	Shader*activeShader;
	glm::mat4 totalRotationTranslation;
	glm::mat4 view;
	glm::mat4 projection;
	std::vector<Shader*> shaders;
	
};

#endif
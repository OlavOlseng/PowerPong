#include "Pipeline.h"


Pipeline::Pipeline(void)
{

}


Shader *Pipeline::getActiveShader()
{
	return this->activeShader;
}
void Pipeline::addShader(Shader *shader,std::string id)
{
	shaders[id] = shader;

}
void Pipeline::useShader(std::string name){
	

	this->activeShader = shaders[name];

}


void Pipeline::setView(glm::mat4 view){

	this->view = view;

}
glm::mat4 Pipeline::getView(){
	return this->view;

}
void Pipeline::setProjection(glm::mat4  projection){

	this->projection = projection;

}
glm::mat4 Pipeline::getProjection(){
	return this->projection;

}


Pipeline::~Pipeline(void)
{
}

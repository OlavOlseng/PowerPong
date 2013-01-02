#include "Pipeline.h"


Pipeline::Pipeline(void)
{
	totalRotationTranslation = glm::mat4(1.0);
}


void Pipeline::clear(){

	totalRotationTranslation = glm::mat4(1.0);
}

Shader *Pipeline::getActiveShader()
{
	return this->activeShader;
}
void Pipeline::addShader(Shader *shader,int id)
{
	if(id >=shaders.size())
		shaders.resize(id+1);
	shaders[id] = shader;

}
void Pipeline::useShader(int id){
	
	if(id < shaders.size())
	this->activeShader = shaders[id];

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


void Pipeline::setTotalRotationTranslation(glm::mat4 value){
	this->totalRotationTranslation = value;

}
glm::mat4 Pipeline::getTotalRotationTranslation(){

	return this->totalRotationTranslation;
}

Pipeline::~Pipeline(void)
{
}

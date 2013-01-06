#include "Pipeline.h"


Pipeline::Pipeline(unsigned int maxDirectionalLights)
{
	
	directionalLights = new DirectionalLight*[maxDirectionalLights];
	numDirectionalLights = 0;
	totalRotationTranslation = glm::mat4(1.0);
}


void Pipeline::clear(){

	for(int i=0;i<numDirectionalLights;i++){
		DirectionalLight * light = directionalLights[i];
		light->transformedDirection = light->direction;
	}

	numDirectionalLights = 0;
	totalRotationTranslation = glm::mat4(1.0);

}

void Pipeline::setViewDirection(glm::vec4 direction){
	this->viewDirection = direction;

}
glm::vec4 Pipeline::getViewDirection(){

	return this->viewDirection;
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
unsigned int Pipeline::getNumDirectionalLights()
{
	return this->numDirectionalLights;

}

void Pipeline::addDirectionalLight(DirectionalLight * light){
	directionalLights[numDirectionalLights] = light;
	numDirectionalLights++;

}

DirectionalLight* Pipeline::getDirectionalLight(unsigned int index){
	return this->directionalLights[index];

}
void Pipeline::popDirectionalLight(unsigned int pops){
	numDirectionalLights-=pops;
}
Pipeline::~Pipeline(void)
{
}

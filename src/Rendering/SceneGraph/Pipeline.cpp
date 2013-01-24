#include "Pipeline.h"


Pipeline::Pipeline(unsigned int maxDirectionalLights,unsigned int maxPointLights)
{
	
	this->maxDirectionalLights = maxDirectionalLights;
	this->maxPointLights = maxPointLights;
	directionalLights = new DirectionalLight*[maxDirectionalLights];
	pointLights = new PointLight*[maxPointLights];
	
	numDirectionalLights = 0;
	numPointLights = 0;
	totalRotationTranslation = glm::mat4(1.0);
	
}


void Pipeline::clear(){

	for(int i=0;i<numDirectionalLights;i++){
		DirectionalLight * light = directionalLights[i];
		light->transformedDirection = light->direction;
	}

	numDirectionalLights = 0;
	numPointLights = 0;
	totalRotationTranslation = glm::mat4(1.0);
	this->view = glm::mat4(1.0);
	this->projection = glm::mat4(1.0);
	childrenNeedUpdate = false;

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
	viewProjectionMatrix = projection*view;
}
glm::mat4 Pipeline::getView(){
	return this->view;

}
void Pipeline::setProjection(glm::mat4  projection){

	this->projection = projection;
	viewProjectionMatrix = projection*view;

}
glm::mat4 Pipeline::getProjection(){
	return this->projection;

}
void Pipeline::setCameraPosition(glm::vec4 position){
	this->cameraPosition = position;
}
glm::vec4 Pipeline::getCameraPosition(){
	return this->cameraPosition;
}


void Pipeline::setTotalRotationTranslation(glm::mat4 value){
	this->totalRotationTranslation = value;

}
glm::mat4 Pipeline::getTotalRotationTranslation(){

	return this->totalRotationTranslation;
}


bool Pipeline::getChildrenNeedsUpdate(){

	return this->childrenNeedUpdate;
}
void Pipeline::setChildrenNeedsUpdate(bool value){

	this->childrenNeedUpdate = value;
}


void Pipeline::setShadowPass(bool shadowPass){
	this->shadowPass = shadowPass;
}
bool Pipeline::isShadowPass(){

	return this->shadowPass;
}
unsigned int Pipeline::getNumDirectionalLights()
{
	return this->numDirectionalLights;

}

void Pipeline::addLight(DirectionalLight*light){
	directionalLights[numDirectionalLights++] = light;
}


DirectionalLight* Pipeline::getDirectionalLight(unsigned int index){
	return this->directionalLights[index];

}
void Pipeline::popDirectionalLight(unsigned int pops){
	numDirectionalLights-=pops;
}



unsigned int Pipeline::getNumPointLights(){
	return numPointLights;
}

void Pipeline::addLight(PointLight * light){

	pointLights[numPointLights++] = light;
}
void Pipeline::popPointlLight(unsigned int pops){
	numPointLights -= pops;

}

glm::mat4 Pipeline::getViewProjectionMatrix(){

	return viewProjectionMatrix;
}
PointLight*Pipeline::getPointLight(unsigned int index){
	return this->pointLights[index];
}
Pipeline::~Pipeline(void)
{
	for(int i = 0;i<maxDirectionalLights;i++){
		delete directionalLights[i];
	}
	delete[] directionalLights;

	for(int i = 0;i<maxPointLights;i++){
		delete pointLights[i];
	}
	delete[] pointLights;
}

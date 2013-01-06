#include "Model.h"


Model::Model()
{

	scale = glm::vec3(1.0,1.0,1.0);

}

glm::vec3 Model::getPosition(){
	return this->position;
}

glm::vec3  Model::getRotation(){
	return this->rotation;

}
glm::vec3  Model::getScale(){
	return this->scale;

}
Material *Model::getMaterial(){
	return &this->material;

}

glm::mat4 Model::getModelMatrix(){
	glm::vec3 pos = getPosition();
	//scale-rotate-translate
	
	glm::mat4 matScale =glm::scale(glm::mat4(1.0),scale);
	glm::mat4 matRot = glm::eulerAngleYXZ(rotation.y,rotation.x,rotation.z);
	glm::mat4 trans = glm::translate(glm::mat4(1.0),pos);

	return trans*matRot*matScale;
	
}


 void Model::setResourceManager(std::shared_ptr<ResourceManager> resourceManager){
	
	 this->resourceManager =  resourceManager;
}
std::shared_ptr<ResourceManager> Model::getResourceManager(){
	
	return resourceManager;

}
void Model::setPosition(glm::vec3 position){
	this->position = position;

}

void Model::setRotation(glm::vec3 rotation){
	this->rotation = rotation;

}
void Model::setScale(glm::vec3 scale){
	this->scale = scale;
}



Model::~Model(void)
{
}

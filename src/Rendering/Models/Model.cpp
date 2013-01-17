#include "Model.h"


Model::Model()
{

	setScale(glm::vec3(1.0,1.0,1.0));

}


Material *Model::getMaterial(){
	return &this->material;

}

glm::mat4 Model::getModelMatrix(){
	glm::vec3 pos = getPosition();
	glm::vec3 rotation = getRotation();
	//scale-rotate-translate
	
	glm::mat4 matScale =glm::scale(glm::mat4(1.0),getScale());
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



Model::~Model(void)
{
}

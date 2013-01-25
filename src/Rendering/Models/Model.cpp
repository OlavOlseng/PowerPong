#include "Model.h"


Model::Model()
{

	setScale(glm::vec3(1.0,1.0,1.0));

}


Material * Model::getMaterial(){
	return &this->material;

}



BoundingBox * Model::getBoundingBox(){

	return &this->boundingBox;
}


glm::mat4 Model::getModelMatrix(){
	
	if(isChanged()){
		setChanged(false);
		glm::vec3 pos = getPosition();
		glm::vec3 rotation = getRotation();
		//scale-rotate-translate
		glm::mat4 rot = glm::eulerAngleYXZ(rotation.y,rotation.x,rotation.z);
		glm::mat4 trans = glm::translate(glm::mat4(1.0),pos);
		glm::mat4 scale = glm::scale(glm::mat4(1.0),this->getScale());

		setCachedModelMatrix(trans*rot*scale*glm::translate(glm::mat4(1.0),-getBoundingBox()->getCenter()));
	}

	return getCachedModelMatrix();
}


void Model::setSize(float width,float height,float depth){
	glm::vec3 origionalSize = this->getBoundingBox()->getSize();

	this->setScale(glm::vec3(width/origionalSize.x,height/origionalSize.y,depth/origionalSize.z));

}
void Model::setSize(glm::vec3 size){
	this->setScale(this->getBoundingBox()->getSize()/size);
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

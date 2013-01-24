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
glm::vec3 Model::getPosition(){
	return Node::getPosition() - this->getBoundingBox()->getCenter();

}
glm::mat4 Model::getModelMatrix(){
	
	if(isChanged()){
		setChanged(false);
		glm::vec3 pos = getPosition();
		glm::vec3 rotation = getRotation();
		//scale-rotate-translate
		setCachedModelMatrix(glm::translate(glm::scale(glm::mat4(1.0),getScale())*glm::eulerAngleYXZ(rotation.y,rotation.x,rotation.z),pos));
	}

	return getCachedModelMatrix();
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

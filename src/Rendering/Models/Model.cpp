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



void Model::setResourceManager(std::shared_ptr<ResourceManager> resourceManager){
	
	 this->resourceManager =  resourceManager;
}
std::shared_ptr<ResourceManager> Model::getResourceManager(){
	
	return resourceManager;

}



Model::~Model(void)
{
}

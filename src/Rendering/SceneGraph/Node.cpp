#include "Node.h"





Node::Node(void)
{
	localScale = glm::vec3(1,1,1);
	
	children = new std::vector<Node*>();
	parent = nullptr;
	changed = true;
	this->cachedModelMatrix = glm::mat4(1.0);
}



void Node::addChild(Node *node)
{
	
	children->push_back(node);
	node->setParent(this);

}

void Node::move(glm::vec3 &amount)
{
	
	this->localPosition += amount;
	changed = true;


}

void Node::addLight(DirectionalLight*light){
	directionalLights.push_back(light);
	

}
void Node::addLight(PointLight*light){

	this->pointLights.push_back(light);
	
}
void Node::scale(glm::vec3 &amount){
	setScale(this->localScale + amount);
	setChanged(true);

}

void Node::setPosition(glm::vec3 &position){
	this->localPosition = position;
	setChanged(true);

}
void Node::setOrientation(glm::vec3 &orientation){
	this->localOrientation = orientation;
	setChanged(true);

}
void Node::setScale(glm::vec3 &scale){

	this->localScale = scale;
	setChanged(true);
}

void Node::rotate(glm::vec3 &amount)
{
	this->localOrientation += amount;
	setChanged(true);

}

void Node::setCachedModelMatrix(glm::mat4 model){
	
	this->cachedModelMatrix = model;
}


glm::vec3 Node::getPosition(){
	return this->localPosition;
}

glm::vec3  Node::getOrientation(){
	return this->localOrientation;

}
glm::vec3  Node::getScale(){
	return this->localScale;

}

glm::mat4 Node::getCachedModelMatrix(){

	return this->cachedModelMatrix;
}







std::vector<Node*> *Node::getChildren(){

	return this->children;
}

void Node::setParent(Node *parent)
{

	this->parent = parent;
}


bool Node::isChanged(){
	return this->changed;

}
void Node::setChanged(bool value){
	this->changed = value;
}





glm::mat4 Node::getModelMatrix(){
	
	if(isChanged()){
		setChanged(false);
		glm::vec3 pos = getPosition();
		glm::vec3 orientation = getOrientation();
		//scale-rotate-translate
		glm::mat4 rot = glm::eulerAngleYXZ(orientation.y,orientation.x,orientation.z);
		glm::mat4 trans = glm::translate(glm::mat4(1.0),pos);
		glm::mat4 scale = glm::scale(glm::mat4(1.0),this->getScale());

		setCachedModelMatrix(trans*rot*scale);
	}

	return getCachedModelMatrix();
}

void Node::render(Pipeline *pipeline)
{
	
	if(changed || pipeline->getChildrenNeedsUpdate()){
		
		
		setCachedModelMatrix(pipeline->getTotalRotationTranslation()*getModelMatrix());

	}

	glm::mat4 modelMatrix = getCachedModelMatrix();
	pipeline->setTotalRotationTranslation(modelMatrix);
	
	
	unsigned int numDirLights = this->directionalLights.size();
	unsigned int numPointLights = this->pointLights.size();
	if(!pipeline->isShadowPass()){

	for(DirectionalLight*light:this->directionalLights){

		light->transformedDirection = modelMatrix*light->direction;
		pipeline->addLight(light);

	}

	for(PointLight*light:this->pointLights){

		light->transformedPosition = modelMatrix*light->position;
		pipeline->addLight(light);

	}
	}

	for(Node *child:*this->children){
		child->render(pipeline);

		pipeline->setTotalRotationTranslation(modelMatrix);
	}

	pipeline->setChildrenNeedsUpdate(false);
	pipeline->popDirectionalLight(numDirLights);
	pipeline->popPointlLight(numPointLights);
	
}

Node::~Node(void)
{
	
	delete children;
}

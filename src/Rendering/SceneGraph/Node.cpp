#include "Node.h"


Node::Node(void)
{
	localScale = glm::vec3(1,1,1);
	
	children = new std::vector<Node*>();
	parent = nullptr;
	changed = true;
}



void Node::addChild(Node *node)
{
	children->push_back(node);
	node->setParent(this);

}

void Node::move(glm::vec3 amount)
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
void Node::scale(glm::vec3 amount){
	this->localScale += amount;
	setChanged(true);

}

void Node::setPosition(glm::vec3 position){
	this->localPosition = position;
	setChanged(true);

}
void Node::setRotation(glm::vec3 rotation){
	this->localRotation = rotation;
	setChanged(true);

}
void Node::setScale(glm::vec3 scale){

	this->localScale = scale;
	setChanged(true);
}

void Node::rotate(glm::vec3 amount)
{
	this->localRotation += amount;
	setChanged(true);

}

void Node::setCachedModelMatrix(glm::mat4 model){
	
	this->cachedModelMatrix = model;
}


glm::vec3 Node::getPosition(){
	return this->localPosition;
}

glm::vec3  Node::getRotation(){
	return this->localRotation;

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
		glm::vec3 rotation = getRotation();
		//scale-rotate-translate
		setCachedModelMatrix(glm::translate(glm::scale(glm::mat4(1.0),getScale())*glm::eulerAngleYXZ(rotation.y,rotation.x,rotation.z),pos));
	}

	return getCachedModelMatrix();
}

void Node::render(Pipeline *pipeline)
{
	
	if(changed || pipeline->getChildrenNeedsUpdate()){
		if(isChanged()){
			setChanged(false);
			glm::mat4 rot = glm::eulerAngleYXZ(localRotation.y,localRotation.x,localRotation.z);
			glm::mat4 trans = glm::translate(glm::mat4(1.0),localPosition);
			glm::mat4 scale = glm::scale(glm::mat4(1.0),this->localScale);
			this->setCachedModelMatrix(trans*rot*scale);
			pipeline->setChildrenNeedsUpdate(true);
		}
		setCachedModelMatrix(pipeline->getTotalRotationTranslation()*getCachedModelMatrix());

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

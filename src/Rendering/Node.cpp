#include "Node.h"


Node::Node(void)
{
	leaves = new std::vector<Model*>();
	children = new std::vector<Node*>();
	parent = nullptr;
}



void Node::addChild(Node *node)
{
	children->push_back(node);
	node->setParent(this);

}
void Node::addChild(Model*model)
{
	leaves->push_back(model);

}
void Node::move(glm::vec3 amount)
{
	
	this->localPosition += amount;


}


void Node::rotate(glm::vec3 amount)
{
	this->localRotation += amount;

	

}
glm::vec3 Node::getGlobalPosition()
{

	return this->globalPosition;

}
glm::vec3 Node::getGlobalRotation(){
	return this->globalRotation;

}

std::vector<Node*> *Node::getChildren(){

	return this->children;
}

void Node::setParent(Node *parent)
{

	this->parent = parent;
}

void Node::render(Pipeline *pipeline)
{
	
	
	glm::mat4 rot = glm::eulerAngleYXZ(localRotation.y,localRotation.x,localRotation.z);
	glm::mat4 trans = glm::translate(glm::mat4(1.0),localPosition);
	
	pipeline->setTotalRotationTranslation(pipeline->getTotalRotationTranslation()*trans*rot);
	
	glm::mat4 oldRotTrans = pipeline->getTotalRotationTranslation();
	
	for(Model* model:*this->leaves){
		
		model->render(pipeline);

	}

	for(Node *child:*this->children){
		child->render(pipeline);

		pipeline->setTotalRotationTranslation(oldRotTrans);
	}

}

Node::~Node(void)
{
}

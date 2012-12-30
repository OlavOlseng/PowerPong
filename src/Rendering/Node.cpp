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

	if(parent)
		this->globalPosition = parent->getGlobalPosition() + localPosition;
	else
		this->globalPosition += localPosition;
	
	for(Node *child:*this->children){
		
		child->move(amount);
	}

	for(Model* model:*this->leaves){
		
		model->setPosition(globalPosition);

	}

}

glm::vec3 Node::getGlobalPosition()
{

	return this->globalPosition;

}

void Node::setParent(Node *parent)
{

	this->parent = parent;
}

void Node::render(Pipeline *pipeline)
{

	
	for(Node *child:*this->children){
		child->render(pipeline);

	}
	for(Model* model:*this->leaves){
		
		model->render(pipeline);

	}

}

Node::~Node(void)
{
}

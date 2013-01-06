#include "Node.h"


Node::Node(void)
{
	localScale = glm::vec3(1,1,1);
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

void Node::addLight(DirectionalLight*light){
	directionalLights.push_back(light);

}
void Node::scale(glm::vec3 amount){
	this->localScale += amount;

}

void Node::setPosition(glm::vec3 position){
	this->localPosition = position;

}
void Node::setRotation(glm::vec3 rotation){
	this->localRotation = rotation;

}
void Node::setScale(glm::vec3 scale){

	this->localScale = scale;
}


void Node::rotate(glm::vec3 amount)
{
	this->localRotation += amount;

	

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
	glm::mat4 scale = glm::scale(glm::mat4(1.0),this->localScale);
	
	pipeline->setTotalRotationTranslation(pipeline->getTotalRotationTranslation()*trans*rot*scale);
	
	glm::mat4 oldRotTrans = pipeline->getTotalRotationTranslation();
	for(DirectionalLight*light:this->directionalLights){

		light->transformedDirection = oldRotTrans*light->direction;
		pipeline->addDirectionalLight(light);

	}

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

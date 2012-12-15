#include "Model.h"


Model::Model()
{

	this->vertexBuffer = new Buffer(Buffer::ARRAY_BUFFER,Buffer::STATIC);
	this->normalBuffer= new Buffer(Buffer::ARRAY_BUFFER,Buffer::STATIC);
	this->texcoordBuffer = new Buffer(Buffer::ARRAY_BUFFER,Buffer::STATIC);
	this->elementBuffer= new Buffer(Buffer::ELEMENT_BUFFER,Buffer::STATIC);

}

glm::vec3 *Model::getPosition(){
	return &this->position;
}
glm::mat4 Model::getModelMatrix(){
	glm::vec3 *pos = getPosition();

	return glm::scale(glm::translate(glm::mat4(1.0),glm::vec3(pos->x,pos->y,pos->z)),glm::vec3(1.0,1.0,1.0));
	
}

void Model::setPosition(glm::vec3 position){
	this->position = position;

}

	
Buffer *Model::getVertexBuffer(){
	return this->vertexBuffer;
}
Buffer*Model::getNormalBuffer(){
	return this->normalBuffer;
}
Buffer * Model::getTexcoordBuffer(){
	return this->texcoordBuffer;
}
Buffer * Model::getElementBuffer(){
	return this->elementBuffer;
}
Model::~Model(void)
{
}

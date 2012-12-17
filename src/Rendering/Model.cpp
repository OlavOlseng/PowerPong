#include "Model.h"


Model::Model()
{



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


void Model::setAttributes(GLint vertexAttrib,GLint normalAttrib,GLint texAttrib) {

	throw "error 500";
}
Model::~Model(void)
{
}

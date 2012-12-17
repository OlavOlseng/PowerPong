#include "StaticModel.h"


StaticModel::StaticModel(void)
{

	this->vertexBuffer = new Buffer(Buffer::ARRAY_BUFFER,Buffer::STATIC);
	this->normalBuffer= new Buffer(Buffer::ARRAY_BUFFER,Buffer::STATIC);
	this->texcoordBuffer = new Buffer(Buffer::ARRAY_BUFFER,Buffer::STATIC);
	this->elementBuffer= new Buffer(Buffer::ELEMENT_BUFFER,Buffer::STATIC);

	glGenBuffers(1,&vao);
}


StaticModel::~StaticModel(void)
{
}

GLuint* StaticModel::getVao(){
		return &vao;

}

void StaticModel::setAttributes(GLint vertexAttrib,GLint normalAttrib,GLint texAttrib){

	printf("hello");
	this->vertexBuffer->setVertexAttribute(vertexAttrib);
	this->normalBuffer->setVertexAttribute(normalAttrib);
	this->texcoordBuffer->setVertexAttribute(texAttrib);
	this->elementBuffer->setVertexAttribute(-1);
	
};
void StaticModel::render(){



	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES,elementBuffer->getBufferSize()/sizeof(GLushort),GL_UNSIGNED_SHORT,0);
	glBindVertexArray(0);
	
};

Buffer *StaticModel::getVertexBuffer(){
	return this->vertexBuffer;
}
Buffer*StaticModel::getNormalBuffer(){
	return this->normalBuffer;
}
Buffer * StaticModel::getTexcoordBuffer(){
	return this->texcoordBuffer;
}
Buffer * StaticModel::getElementBuffer(){
	return this->elementBuffer;
}

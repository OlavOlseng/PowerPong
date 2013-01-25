#include "Buffer.h"

Buffer::Buffer(BufferType bufferType,BufferDrawMode  drawingMode,unsigned int stepsize,int dataType)
{
	_bufferType = bufferType;
	_drawMode = drawingMode;
	_needsInit = true;
	_bufferHandle = 0;
	this->stepsize = stepsize;
	this->dataType = dataType;
}

void Buffer::init(){
	_needsInit = false;
	ShaderUtil::prepareBuffer(_bufferHandle,_bufferType);

}
void Buffer::setData(GLvoid * data,int size){
	if(_needsInit)
		init();
	_size = size;

	glBindBuffer(_bufferType,_bufferHandle);
	glBufferData(_bufferType,_size,data,_drawMode);

}
void Buffer::setVertexAttribute(GLint attrib){

	this->vertexAttribute = attrib;

}
GLint Buffer::getVertexAttribute(){
	return this->vertexAttribute;
}
int Buffer::getBufferSize(){

	return _size;
}
void Buffer::bindTo(GLint vertexAttribute){
	glBindBuffer(_bufferType,_bufferHandle);
	glEnableVertexAttribArray(vertexAttribute);
	glVertexAttribPointer(vertexAttribute, stepsize, dataType, GL_FALSE, 0, 0);
}
void Buffer::bind(){
	glBindBuffer(_bufferType,_bufferHandle);

}
GLuint Buffer::getBufferHandle(){

	return _bufferHandle;
}

void Buffer::setBufferHandle(GLuint handle){
	this->_bufferHandle = handle;
	_needsInit = false;

}
Buffer::~Buffer()
{
	
}

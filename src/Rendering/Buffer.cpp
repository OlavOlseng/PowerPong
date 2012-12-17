#include "Buffer.h"

Buffer::Buffer(BufferType bufferType,BufferDrawMode  drawingMode)
{
	_bufferType = bufferType;
	_drawMode = drawingMode;
	_needsInit = true;
	_bufferHandle = 0;
}

void Buffer::init(){
	prepareBuffer(_bufferHandle,_bufferType);

}
void Buffer::setData(GLvoid * data,int size){
	if(_needsInit)
		init();
	_size = size;
	if(vertexAttribute < 0 && _bufferType != Buffer::ELEMENT_BUFFER)
		return;
	if(_bufferType == Buffer::ARRAY_BUFFER){
	
	glBindBuffer(_bufferType,_bufferHandle);
	glBufferData(_bufferType,_size,data,_drawMode);
	glEnableVertexAttribArray(vertexAttribute);
	glVertexAttribPointer(vertexAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	}else{

	glBindBuffer(_bufferType,_bufferHandle);
	glBufferData(_bufferType,_size,data,_drawMode);

	}
}
void Buffer::setVertexAttribute(GLint attrib){

	this->vertexAttribute = attrib;

}
int Buffer::getBufferSize(){

	return _size;
}
GLuint Buffer::getBufferHandle(){

	return _bufferHandle;
}

Buffer::~Buffer()
{
	
}

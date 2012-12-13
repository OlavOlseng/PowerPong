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
	glBindBuffer(_bufferType,_bufferHandle);
	glBufferData(GL_ARRAY_BUFFER,_size,data,_drawMode);

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

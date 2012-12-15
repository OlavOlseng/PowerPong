
#ifndef game_engine_buffer_h
#define game_engine_buffer_h
#include "shader_util.h"
#include <GL\glew.h>
#include <GL\freeglut.h>

class Buffer
{
public:
	enum BufferType{ARRAY_BUFFER=GL_ARRAY_BUFFER, ELEMENT_BUFFER = GL_ELEMENT_ARRAY_BUFFER};
	enum BufferDrawMode{STATIC=GL_STATIC_DRAW};

	Buffer(BufferType bufferType,BufferDrawMode drawingMode);
	~Buffer();
	void setData(GLvoid * data,int size);
	GLuint getBufferHandle();
	int getBufferSize();
private:
	GLuint  _bufferHandle;
	BufferType _bufferType;
	BufferDrawMode _drawMode;
	int _size;
	bool _needsInit;
	void init();
	
};




#endif

#ifndef game_engine_buffer_h
#define game_engine_buffer_h
#include "shader_util.h"
#include <GL\glew.h>
#include <GL\freeglut.h>

class Buffer
{
public:
	enum BufferType{ARRAY_BUFFER=GL_ARRAY_BUFFER, ELEMENT_BUFFER = GL_ELEMENT_ARRAY_BUFFER};
	enum BufferDrawMode{STATIC=GL_STATIC_DRAW, DYNAMIC = GL_DYNAMIC_DRAW};

	Buffer(BufferType bufferType,BufferDrawMode drawingMode,unsigned int stepsize,int dataType);
	~Buffer();
	void setData(GLvoid * data,int size);
	GLuint getBufferHandle();
	int getBufferSize();
	void setVertexAttribute(GLint attrib);
	GLint getVertexAttribute();
	void bindTo(GLint vertexAttribute);
	void bind();
	void init();
	void setBufferHandle(GLuint handle);
private:
	GLuint  _bufferHandle;
	GLint vertexAttribute;
	BufferType _bufferType;
	BufferDrawMode _drawMode;
	int dataType;
	unsigned int stepsize;
	int _size;
	bool _needsInit;
	
	
};




#endif
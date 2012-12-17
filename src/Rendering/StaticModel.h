#ifndef static_model_h
#define static_model_h

#include <GL\glew.h>
#include <GL\freeglut.h>;
#include <GL\GL.h>
#include <GL\GLU.h>

#include "Model.h"
#include "Buffer.h"
class StaticModel:public Model
{
public:
	StaticModel(void);
	~StaticModel(void);

	Buffer *getVertexBuffer();
	Buffer*getNormalBuffer();
	Buffer * getTexcoordBuffer();
	Buffer * getElementBuffer();
	void setAttributes(GLint vertexAttrib,GLint normalAttrib,GLint texAttrib);
	void render();
	
	GLuint* getVao();
private:

	Buffer *vertexBuffer;
	Buffer*normalBuffer;
	Buffer * texcoordBuffer;
	Buffer * elementBuffer;

	GLuint vao;
};

#endif
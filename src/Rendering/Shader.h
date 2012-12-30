#ifndef shader_h
#define shader_h
#include <string>
#include <GL\glew.h>
#include <GL\freeglut.h>;
#include <GL\GL.h>
#include <GL\GLU.h>
#include "shader_util.h"



class Shader
{
public:
	Shader(std::string vs,std::string fs);
	~Shader(void);
	GLuint getAttributeCoord3D();
	GLuint getAttributeNormal3D();
	GLuint getAttributeTexCoord2D();
	void setUniformMat4f(unsigned int uniform,float*value);
	void bindUniform(unsigned int uniform,std::string name);
	void bind();
	void unbind();

private:
	bool bound;
	GLint program;
	GLint attributeCoord3D;
	GLint attributeTexcoord2D;
	GLint attributeNormal3D;
	GLint uniformMVP;
	GLint*uniforms;

};







#endif
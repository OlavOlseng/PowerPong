#ifndef shader_h
#define shader_h
#include <string>
#include <GL\glew.h>
#include <GL\freeglut.h>;
#include <GL\GL.h>
#include <GL\GLU.h>
#include "shader_util.h"
#include <vector>
#include <string>
#include "ShaderUniforms.h"
#include "ShaderAttributes.h"

class Shader
{
public:
	Shader(std::string vs,std::string fs);
	~Shader(void);
	
	void setUniformMat4f(unsigned int uniform,float*value);
	void setUniformFloat(unsigned int uniform,float value);
	void bindUniform(unsigned int uniform,std::string name);
	void bindAttribute(unsigned int attribute,std::string name);
	void bind();
	void unbind();
	GLint* getAttributes();
private:
	bool bound;
	GLint program;
	GLint*uniforms;
	GLint*attributes;

};







#endif
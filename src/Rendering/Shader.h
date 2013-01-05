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
#include <sstream>
#include "ShaderUniforms.h"
#include "ShaderAttributes.h"

class Shader
{
public:
	Shader(std::string vs,std::string fs,unsigned int numUniforms = ShaderUniforms::NUM_UNIFORMS,unsigned int numAttributes = ShaderAttributes::NUM_ATTRIBUTES,unsigned int numUniformStructs = ShaderAttributes::NUM_ATTRIBUTES);
	~Shader(void);
	
	void setUniformMat4f(unsigned int uniform,float*value);
	void setUniformFloat(unsigned int uniform,float value);
	void setUniformVec3f(unsigned int uniform,float*value);
	void setUniformVec3f(unsigned int uniform,float v1,float v2,float v3);
	void setUniformStructVec3f(unsigned int structArray,int index, unsigned int uniform,float v1,float v2,float v3);
	void setUniformStructFloat(unsigned int structArray,int index, unsigned int uniform,float value);
	void setUniformInt(unsigned int uniform,int value);

	void bindUniform(unsigned int uniform,std::string name);
	void bindUniformStructArray(unsigned int uniform,unsigned int arraySize,unsigned int memberCount,const char*structName,const char **structMemberNames);
	GLint **getStructArray(unsigned int uniform);
	GLint*getStruct(unsigned int uniform,int i);
	void bindAttribute(unsigned int attribute,std::string name);
	void bind();
	void unbind();
	GLint* getAttributes();
private:
	bool bound;
	GLint program;
	GLint*uniforms;
	GLint*attributes;

	
	GLint *** uniformStructs;

};







#endif
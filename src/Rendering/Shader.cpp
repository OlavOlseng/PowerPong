#include "Shader.h"


Shader::Shader(std::string vs,std::string fs)
{
	this->program = ShaderUtil::compileShaders(vs.c_str(),fs.c_str());
	
	attributeCoord3D = ShaderUtil::bindAttribute(program,"coord3d");
	attributeNormal3D = ShaderUtil::bindAttribute(program,"normal3d");
	attributeTexcoord2D = ShaderUtil::bindAttribute(program,"texcoord2d");
	
	uniforms = new GLint[20];
	bound = false;
}



GLuint Shader::getAttributeCoord3D()
{
	return this->attributeCoord3D;
	
}

GLuint Shader::getAttributeNormal3D()
{

	return this->attributeNormal3D;
}

GLuint Shader::getAttributeTexCoord2D()
{
	return this->attributeTexcoord2D;

}

void Shader::setUniformMat4f(unsigned int uniform,float*value)
{

	glUniformMatrix4fv(uniforms[uniform],1,GL_FALSE,value);

}

void Shader::bindUniform(unsigned int uniform,std::string name)
{
	uniforms[uniform] = ShaderUtil::bindUniform(this->program,name.c_str());


}

void Shader::bind(){
	if(!bound){
		glUseProgram(this->program);
		bound = true;
	}

}

void Shader::unbind(){
	if(bound){
		glUseProgram(0);
		bound = false;
	}
	

}


Shader::~Shader(void)
{
	delete[] uniforms;
}
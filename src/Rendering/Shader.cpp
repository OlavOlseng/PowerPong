#include "Shader.h"


Shader::Shader(std::string vs,std::string fs)
{
	this->program = ShaderUtil::compileShaders(vs.c_str(),fs.c_str());
		
	uniforms = new GLint[ShaderUniforms::NUM_UNIFORMS];
	attributes = new GLint[ShaderAttributes::NUM_ATTRIBUTES];

	bound = false;
}


void Shader::bindAttribute(unsigned int attribute,std::string name){
	attributes[attribute] = ShaderUtil::bindAttribute(program,name.c_str());

}

void Shader::setUniformMat4f(unsigned int uniform,float*value)
{

	glUniformMatrix4fv(uniforms[uniform],1,GL_FALSE,value);

}
void Shader::setUniformFloat(unsigned int uniform,float value){
	glUniform1f(uniforms[uniform],value);

}
void Shader::bindUniform(unsigned int uniform,std::string name)
{
	uniforms[uniform] = ShaderUtil::bindUniform(this->program,name.c_str());


}
GLint* Shader::getAttributes(){

	return this->attributes;
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
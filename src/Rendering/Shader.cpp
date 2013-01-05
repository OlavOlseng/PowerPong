#include "Shader.h"


Shader::Shader(std::string vs,std::string fs,unsigned int numUniforms,unsigned int numAttributes,unsigned int numUniformStructs)
{
	this->program = ShaderUtil::compileShaders(vs.c_str(),fs.c_str());
		
	uniforms = new GLint[numUniforms];
	attributes = new GLint[numAttributes];
	uniformStructs = new GLint**[numUniformStructs];

		bound = false;
}


void Shader::bindAttribute(unsigned int attribute,std::string name){
	attributes[attribute] = ShaderUtil::bindAttribute(program,name.c_str());

}

void Shader::setUniformMat4f(unsigned int uniform,float*value)
{

	glUniformMatrix4fv(uniforms[uniform],1,GL_FALSE,value);

}
void Shader::setUniformVec3f(unsigned int uniform,float*value){

	glUniform3f(uniforms[uniform],value[0],value[1],value[2]);
}
void Shader::setUniformVec3f(unsigned int uniform,float v1,float v2,float v3){

	glUniform3f(uniforms[uniform],v1,v2,v3);
}
void Shader::setUniformFloat(unsigned int uniform,float value){
	glUniform1f(uniforms[uniform],value);

}

void Shader::setUniformInt(unsigned int uniform,int value){
	glUniform1i(uniforms[uniform],value);
}

void Shader::setUniformStructVec3f(unsigned int structArray,int index, unsigned int uniform,float v1,float v2,float v3){

	glUniform3f(this->getStruct(structArray,index)[uniform],v1,v2,v3);

}
void Shader::setUniformStructFloat(unsigned int structArray,int index, unsigned int uniform,float value){

	glUniform1f(this->getStruct(structArray,index)[uniform],value);
}
void Shader::bindUniformStructArray(unsigned int uniform,unsigned int count,unsigned int memberCount,const char*structName,const char **structMemberNames){
	
	GLint ** uniformStructArray = new GLint*[count];

	for(int i = 0;i<count;i++){

		GLint* uniformStruct = new GLint[memberCount];

		for(int j = 0;j<memberCount;j++){
			 std::ostringstream stringStream;
			 stringStream << structName <<"["<<i<<"]." << structMemberNames[j];
			 uniformStruct[j] = ShaderUtil::bindUniform(this->program,stringStream.str().c_str());;
		}
		uniformStructArray[i] = uniformStruct;
		
	}
	this->uniformStructs[uniform] = uniformStructArray;
	

}

GLint **Shader::getStructArray(unsigned int uniform){

	return uniformStructs[uniform];

}
GLint* Shader::getStruct(unsigned int uniform,int i){

	return uniformStructs[uniform][i];
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
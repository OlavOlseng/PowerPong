//
//  shader_util.cpp
//  openglbook
//
//  Created by Ellen Johansen on 6/4/12.
//  Copyright (c) 2012 Voksenopplæringen. All rights reserved.
//


#include "shader_util.h"


std::string ShaderUtil::readShaderFile(std::string fName){
	std::cout << "Reading shader file: "<< fName<< std::endl;

	std::stringstream shaderFile;
	std::string input;
    std::ifstream file;
    file.open(fName.c_str(),std::ios::in);
   
    file.clear();


    if(file.good() && file.is_open()){
		while(!file.eof()){
			std::getline(file,input);
			shaderFile << input + "\n";
		}
		
    }else{
        if(file.badbit){
            std::cout<<"Error on file reading:badbit"<<std::endl;

        }else{
            std::cout << "Error on file reading"<<std::endl;
        }
       
 
    }
    file.clear();
    file.close();
	return shaderFile.str();
}
GLuint ShaderUtil::loadTexture(std::string fName){
	

	GLuint tex=  SOIL_load_OGL_texture(fName.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO|SOIL_FLAG_COMPRESS_TO_DXT|SOIL_FLAG_INVERT_Y|SOIL_FLAG_MIPMAPS);
	
       if(tex == 0){
		   std::cout<< "Error on loading texture: "<<fName.c_str() <<std::endl;
		}
    
    return tex;


}

GLuint ShaderUtil::compileShaders(std::string vs,std::string fs){


	std::string vsSource = readShaderFile(vs);
	std::string fsSource = readShaderFile(fs);
	return compileShaders(vsSource.c_str(),fsSource.c_str());

}
GLuint ShaderUtil::compileShaders(std::string name){
	return compileShaders(name +".vert",name + ".frag");

}
GLuint ShaderUtil::compileShaders( const char*vs_source,const char*fs_source){
    GLint link_ok = GL_FALSE,vs_ok = GL_FALSE,fs_ok = GL_FALSE;
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    

    
  
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &fs_ok);
    if (!fs_ok) {
        printf("\n error on compiling fragment shader\n");
    }
	char infoBufferFS[512];
	glGetShaderInfoLog(fs,512,NULL,infoBufferFS);
	printf("\nShaderLog fragmentShader: %s \n",infoBufferFS);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &vs_ok);
    if (!vs_ok) {
        printf("\n error on compiling vertex shader\n");
    }
	char infoBufferVS[512];
	glGetShaderInfoLog(vs,512,NULL,infoBufferVS);
	printf("\nShaderLog vertexShader: %s \n",infoBufferVS);
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    
    glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
 
    if(!link_ok){
        printf("Error on linking shaders\n");
    }
	 
	
    return program;
}
void ShaderUtil::prepareBuffer(GLuint &name,GLenum target){
    glGenBuffers(1, &name);
    glBindBuffer(target,name);
    
}
void ShaderUtil::bufferStaticArray(GLenum target,GLvoid*data,size_t size){
    
    glBufferData(target, size, data, GL_STATIC_DRAW);
    
	
}


GLint ShaderUtil::bindAttribute(GLuint program,const char* attr){
    GLint attribute = glGetAttribLocation(program, attr);
    if(attribute == -1){
		printf( "Could not bind attribute %s\n", attr);
        }
    return attribute;
}
GLint ShaderUtil::bindUniform(GLuint program,const char *uni){
    GLint uniform = glGetUniformLocation(program, uni);
    if(uniform == -1){
		printf( "Could not bind uniform %s\n", uni);
    }
    return  uniform;
}

                    


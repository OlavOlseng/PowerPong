//
//  shader_util.cpp
//  openglbook
//
//  Created by Ellen Johansen on 6/4/12.
//  Copyright (c) 2012 Voksenopplæringen. All rights reserved.
//


#include "shader_util.h"


char* ShaderUtil::readShaderFile(std::string fName){
	std::cout << fName.c_str() << std::endl;

    std::ifstream file;
    file.open(fName.c_str(),std::ios::in);
   
    file.clear();
    char*buffer;
    if(file.good() && file.is_open()){
       
        file.seekg(0, std::ios_base::end);
        long len = file.tellg();
        file.seekg(0,std::ios_base::beg);
        buffer = new char[len];
        file.read(buffer, len-1);
        
		
        if( !file.good()){
             std::cout<<"error on file reading2"<<std::endl; 
        }
        
    }else{
        if(file.badbit){
            std::cout<<"error on file reading:badbit"<<std::endl;

        }else{
            std::cout << "error on file reading"<<std::endl;
        }
       
 
    }
    file.clear();
    file.close();
    return buffer;
}
GLuint ShaderUtil::loadTexture(std::string fName,GLuint id){
	

    GLuint tex=  SOIL_load_OGL_texture(fName.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_POWER_OF_TWO|SOIL_FLAG_COMPRESS_TO_DXT|SOIL_FLAG_INVERT_Y
                                           );

       if(tex == 0){
		   std::cout<< "error on loading texture: "<<fName.c_str() <<std::endl;
		}
    
    
    return tex;


}
GLuint ShaderUtil::compileShaders( const char*vs_source,const char*fs_source){
    GLint link_ok = GL_FALSE,vs_ok = GL_FALSE,fs_ok = GL_FALSE;
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    

    
  
      glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &fs_ok);
    if (!fs_ok) {
        printf("error on compiling fragment shader\n");
    }

    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &vs_ok);
    if (!vs_ok) {
        printf("error on compiling vertex shader\n");
    }
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

                    


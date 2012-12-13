//
//  shader_util.h
//  openglbook
//
//  Created by Ellen Johansen on 6/4/12.
//  Copyright (c) 2012 Voksenopplæringen. All rights reserved.
//

#ifndef openglbook_shader_util_h
#define openglbook_shader_util_h

#include <string.h>
#include <fstream>
#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>





char* readShaderFile(std::string fName);
GLuint compileShaders(const char*vs_source,const char*fs_source);

void prepareBuffer(GLuint &name,GLenum target);
void bufferStaticArray(GLenum target,GLvoid*data,size_t size);


GLint bindAttribute(GLuint program,char* attr);
GLint bindUnifrom(GLuint program,char *uni);

GLuint loadTexture(std::string fName,GLuint id);
#endif

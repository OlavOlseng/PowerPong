

#ifndef openglbook_shader_util_h
#define openglbook_shader_util_h

#include <string>
#include <fstream>
#include <iostream>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <sstream>
#include <SOIL.h>

namespace ShaderUtil{

std::string readShaderFile(std::string fName);
GLuint compileShaders(const char*vs_source,const char*fs_source);
GLuint compileShaders(std::string vs,std::string fs);
GLuint compileShaders(std::string name);
void prepareBuffer(GLuint &name,GLenum target);
void bufferStaticArray(GLenum target,GLvoid*data,size_t size);


GLint bindAttribute(GLuint program,const char *attr);
GLint bindUniform(GLuint program,const char *uni);

GLuint loadTexture(std::string fName);
}
#endif

#include "Texture.h"


Texture::Texture(GLuint textureHandle)
{

	this->textureHandle = textureHandle;

	
}

Texture::Texture(ColorFormat format,int width,int height){

	this->width = width;
	this->height = height;
	glGenTextures(1,&textureHandle);
	bind();
	glTexImage2D(GL_TEXTURE_2D,0,format,width,height,0,format,GL_UNSIGNED_BYTE,0);

}

void Texture::setMinFilter(Filter minFilter){

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,minFilter);
	this->minFilter = minFilter;
}
void Texture::setMagFilter(Filter magFilter){
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,magFilter);
	this->magFilter = magFilter;
}
void Texture::bind(){
	glBindTexture(GL_TEXTURE_2D,textureHandle);

}
GLuint Texture::getTextureHandle(){

	return this->textureHandle;
}

Texture::~Texture(void)
{
}

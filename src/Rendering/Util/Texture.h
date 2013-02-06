#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL\glew.h>
#include <GL\GL.h>
#include <string>
class Texture
{
public:
	enum ColorFormat{FORMAT_RGB=GL_RGB,FORMAT_RGBA=GL_RGBA};
	enum Filter{NEAREST = GL_NEAREST,LINEAR = GL_LINEAR};

	Texture(GLuint textureHandle);
	
	Texture(ColorFormat format,int width,int height);
	~Texture(void);

	GLuint getTextureHandle();

	void setMinFilter(Filter minFilter);
	void setMagFilter(Filter magFilter);
	void bind();

private:
	GLuint textureHandle;
	int width,height;
	Filter magFilter,minFilter;
};

#endif
#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H
#include <GL\glew.h>
#include <GL\GL.h>
#include "Texture.h"
#include <vector>
class FrameBuffer
{
public:
	FrameBuffer(void);
	~FrameBuffer(void);

	void setDepthBuffer(int width,int height);
	void addRenderTexture(Texture * texture);
	void bind();
private:
	GLuint bufferHandle;
	GLuint depthBufferHandle;
	std::vector<Texture * > renderTextures;

};


#endif
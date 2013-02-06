#include "FrameBuffer.h"


FrameBuffer::FrameBuffer(void)
{
	bufferHandle = 0;
	depthBufferHandle = 0;

	glGenFramebuffers(1,&bufferHandle);
	

}
void FrameBuffer::setDepthBuffer(int width,int height){
	glBindFramebuffer(GL_FRAMEBUFFER,bufferHandle);
	glGenRenderbuffers(1,&depthBufferHandle);
	glBindRenderbuffer(GL_RENDERBUFFER,depthBufferHandle);
	glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH_COMPONENT,width,height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_RENDERBUFFER,depthBufferHandle);
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	

}

void FrameBuffer::addRenderTexture(Texture * texture){

	renderTextures.push_back(texture);
	glBindFramebuffer(GL_FRAMEBUFFER,bufferHandle);
	glFramebufferTexture(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,texture->getTextureHandle(),0);
	GLenum DrawBuffers[2] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1,DrawBuffers);
	glBindFramebuffer(GL_FRAMEBUFFER,0);

}
void FrameBuffer::bind(){

	glBindFramebuffer(GL_FRAMEBUFFER,bufferHandle);
}

FrameBuffer::~FrameBuffer(void)
{
	glDeleteFramebuffers(1,&bufferHandle);
	
	
}

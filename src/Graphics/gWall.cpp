#include "gWall.h"


gWall::gWall(int blockScale,int lenght,glm::vec3 pos):vertexBuffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,3,GL_FLOAT),colorBuffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,3,GL_FLOAT)
{


	setPosition(pos);
	this->blockScale = blockScale;

	this->width = lenght;
	
	blocks = new gBlock[width];
	
	glGenVertexArrays(1,&vao);
	//Physics init
	
}
int gWall::getWidth(){
	return this->width;
}
void gWall::setBlock(int x,int width,glm::vec3 color){

	for (int i = x;i<x+width;i++)
		blocks[i].set(width,color);
	
	

}

gBlock gWall::getBlock(int x){

	
	gBlock block = blocks[x];
	return block;

}

Buffer *gWall::getVertexBuffer(){
	
	return &this->vertexBuffer;
	
}
Buffer*gWall::getColorBuffer(){

	return &this->colorBuffer;

}


void gWall::setAttributes(GLint*attributes){
	this->vertexBuffer.setVertexAttribute(attributes[ShaderAttributes::COORD3D]);
	this->colorBuffer.setVertexAttribute(attributes[ShaderAttributes::COLOR3D]);

}
GLuint* gWall::getVao(){
	return &vao;
}
void gWall::setShader(int id){
	this->shaderName = id;
}
int gWall::getShader(){
	return this->shaderName;
}



void gWall::render(Pipeline *pipeline){
	pipeline->useShader(shaderName);
	Shader*shader = pipeline->getActiveShader();
	shader->bind();
	glm::mat4 model = pipeline->getTotalRotationTranslation()*getModelMatrix();

	glm::mat4 mvp = pipeline->getProjection()*pipeline->getView()*model;
	shader->setUniformMat4f(ShaderUniforms::MVP,glm::value_ptr(mvp));
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES,0,vertexBuffer.getBufferSize());

	glBindVertexArray(0);
	shader->unbind();
	
};
gWall::~gWall(void)
{

}

#include "gWall.h"


gWall::gWall(int blockScale,int lenght,glm::vec3 pos):vertexBuffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,3,GL_FLOAT),
	colorBuffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,3,GL_FLOAT),typeBuffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,1,GL_FLOAT)
{

	
	
	this->blockScale = blockScale;

	this->width = lenght;
	
	blocks = new gBlock[width];
	glGenVertexArrays(1,&vao);

	setPosition(pos);
	
	
}
int gWall::getWidth(){
	return this->width;
}

void gWall::init(){
	

		
	textureHandle = ShaderUtil::loadTexture(getResourceManager()->getWorkingDirectiory() + "tileAtlas.png",0);

	glBindTexture(GL_TEXTURE_2D,textureHandle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 




}
void gWall::setBlock(int x,int width,glm::vec3 color){

	for (int i = x;i<x+width;i++)
		blocks[i].set(width,color);
	

}
void gWall::setBlock(int x,int width,gBlock::BlockType type){
	for (int i = x;i<x+width;i++)
		blocks[i].set(width,type);


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

Buffer * gWall::getTypeBuffer(){

	return &this->typeBuffer;
}
void gWall::setAttributes(GLint*attributes){
	this->vertexBuffer.setVertexAttribute(attributes[ShaderAttributes::COORD3D]);
	this->colorBuffer.setVertexAttribute(attributes[ShaderAttributes::COLOR3D]);
	this->typeBuffer.setVertexAttribute(attributes[ShaderAttributes::BLOCK_TYPE]);

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
	shader->setUniformFloat(ShaderUniforms::STEP_SIZE,0.25);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,textureHandle);
	glBindVertexArray(vao);

	glDrawArrays(GL_TRIANGLES,0,vertexBuffer.getBufferSize());

	glBindVertexArray(0);
	shader->unbind();
	
};
gWall::~gWall(void)
{

}

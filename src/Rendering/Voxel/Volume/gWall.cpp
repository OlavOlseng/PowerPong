#include "gWall.h"


gWall::gWall(int blockScale,int lenght,glm::vec3 pos):vertexBuffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,3,GL_FLOAT),
	colorBuffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,3,GL_FLOAT),typeBuffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,1,GL_FLOAT),
	normalBuffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,3,GL_FLOAT)
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
	

		
	textureHandle = resourceManager->loadTexture("tileAtlas.png");

	glBindTexture(GL_TEXTURE_2D,textureHandle);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
	Material*material = this->getMaterial();
	material->ambient = glm::vec3(1.0,1.0,1.0);
	material->diffuse = glm::vec3(1.0,1.0,1.0);
	material->specular = glm::vec3(1.0,1.0,1.0);
	material->shininess = 0.7;


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



Buffer * gWall::getNormalBuffer(){
	return &this->normalBuffer;

}
Buffer*gWall::getColorBuffer(){

	return &this->colorBuffer;

}

Buffer * gWall::getTypeBuffer(){

	return &this->typeBuffer;
}
void gWall::setAttributes(GLint*attributes,GLint*shadowAttributes){
	this->vertexBuffer.setVertexAttribute(attributes[ShaderAttributes::COORD3D]);
	this->colorBuffer.setVertexAttribute(attributes[ShaderAttributes::COLOR3D]);
	this->typeBuffer.setVertexAttribute(attributes[ShaderAttributes::BLOCK_TYPE]);
	this->normalBuffer.setVertexAttribute(attributes[ShaderAttributes::NORMAL3D]);

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


	if(pipeline->isShadowPass())
		return;

	pipeline->useShader(shaderName);
	Shader*shader = pipeline->getActiveShader();
	shader->bind();
	glm::vec4 viewDirection = pipeline->getViewDirection();
	unsigned int numDirLights = pipeline->getNumDirectionalLights();
	unsigned int numPointLights = pipeline->getNumPointLights();

	shader->setUniformInt(ShaderUniforms::NUM_DIRECTIONAL_LIGHTS,numDirLights);
	shader->setUniformInt(ShaderUniforms::NUM_POINT_LIGHTS,numPointLights);
	shader->setUniformVec4f(ShaderUniforms::VIEW_DIRECTION,viewDirection.x,viewDirection.y,viewDirection.z,0.0);
	
	for(int i = 0;i<numDirLights;i++){
		DirectionalLight*light = pipeline->getDirectionalLight(i);
		//diffuse
		shader->setUniformStructVec4f(ShaderUniforms::LIGHT_DIRECTIONAL,i,0,light->diffuse.x,light->diffuse.y,light->diffuse.z,light->diffuse.w);
		//specular
		shader->setUniformStructVec4f(ShaderUniforms::LIGHT_DIRECTIONAL,i,1,light->specular.x,light->specular.y,light->specular.z,light->specular.w);
		//direction
		shader->setUniformStructVec4f(ShaderUniforms::LIGHT_DIRECTIONAL,i,2,light->transformedDirection.x,light->transformedDirection.y,light->transformedDirection.z,0.0);
		
	}

	for(int i = 0;i< numPointLights;i++){
		PointLight *light = pipeline->getPointLight(i);

		//diffuse
		shader->setUniformStructVec4f(ShaderUniforms::LIGHT_POINT,i,0,light->diffuse.x,light->diffuse.y,light->diffuse.z,light->diffuse.w);
		//specular
		shader->setUniformStructVec4f(ShaderUniforms::LIGHT_POINT,i,1,light->specular.x,light->specular.y,light->specular.z,light->specular.w);
		//position
		shader->setUniformStructVec4f(ShaderUniforms::LIGHT_POINT,i,2,light->transformedPosition.x,light->transformedPosition.y,light->transformedPosition.z,0.0);
		//constantAttenuation
		shader->setUniformStructFloat(ShaderUniforms::LIGHT_POINT,i,3,light->constantAttenuation);
		//linearAttenuation
		shader->setUniformStructFloat(ShaderUniforms::LIGHT_POINT,i,4,light->linearAttenutation);
		//quadraticAttenuation
		shader->setUniformStructFloat(ShaderUniforms::LIGHT_POINT,i,5,light->quadraticAttenuation);


	}
	//set material
	Material * material = this->getMaterial();
	glm::vec3 diffuse = material->diffuse;
	glm::vec3 ambient = material->ambient;
	glm::vec3 specular = material->specular;
	float shininess = material->shininess;

	shader->setUniformVec4f(ShaderUniforms::MATERIAL_DIFFUSE,diffuse.x,diffuse.y,diffuse.z,1.0);
	shader->setUniformVec4f(ShaderUniforms::MATERIAL_AMBIENT,ambient.x,ambient.y,ambient.z,1.0);
	shader->setUniformVec4f(ShaderUniforms::MATERIAL_SPECULAR,specular.x,specular.y,specular.z,1.0);
	shader->setUniformFloat(ShaderUniforms::MATERIAL_SHININESS,shininess);

	glm::mat4 model = pipeline->getTotalRotationTranslation()*getModelMatrix();
	glm::mat4 mvp = pipeline->getProjection()*pipeline->getView()*model;
	shader->setUniformMat4f(ShaderUniforms::MODEL,glm::value_ptr(model));
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

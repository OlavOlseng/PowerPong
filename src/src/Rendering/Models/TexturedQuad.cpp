#include "TexturedQuad.h"


TexturedQuad::TexturedQuad(std::shared_ptr<ResourceManager> resourceManager):Model(resourceManager)
{

	vertexBuffer = new Buffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,3,GL_FLOAT);
	textureBuffer = new Buffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,2,GL_FLOAT);


}

void TexturedQuad::init(Texture * texture){


	this->shader = resourceManager->loadShader("sprite2DShader");
	shader->bindUniform(ShaderUniforms::MVP,"mvp");
	shader->bindAttribute(ShaderAttributes::COORD3D,"coord3d");
	shader->bindAttribute(ShaderAttributes::TEXCOORD2D,"texcoord2d");

	setAttributes(shader->getAttributes());


	float  vertices[18] = {  -1.0f, -1.0f, 0.0f,
							 1.0f, -1.0f, 0.0f,
							-1.0f,  1.0f, 0.0f,
							-1.0f,  1.0f, 0.0f,
							 1.0f, -1.0f, 0.0f,
							 1.0f,  1.0f, 0.0f,
	};
	float texcoords[12] = { 0.0f,0.0f,
							1.0f,0.0f,
							0.0f,1.0f,
							0.0f,1.0f,
							1.0f,0.0f,
							1.0f,1.0f };



	this->texture = texture;
	this->texture->bind();
	this->texture->setMagFilter(Texture::Filter::NEAREST);
	this->texture->setMinFilter(Texture::Filter::NEAREST);

	vertexBuffer->setData(vertices,sizeof(float)*18);
	textureBuffer->setData(texcoords,sizeof(float)*12);
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);

	vertexBuffer->bindTo(vertexBuffer->getVertexAttribute());
	textureBuffer->bindTo(textureBuffer->getVertexAttribute());
	glBindVertexArray(0);

	this->getBoundingBox()->setBounds(-1,1,-1,1,-1,1);


}

void TexturedQuad::render(Pipeline *pipeline){


	shader->bind();

	glm::mat4 model = pipeline->getTotalRotationTranslation()*getModelMatrix();
	glm::mat4 mvp = pipeline->getProjection()*pipeline->getView()*model;
	shader->setUniformMat4f(ShaderUniforms::MVP,glm::value_ptr(mvp));

	glActiveTexture(GL_TEXTURE0);
	texture->bind();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES,0,vertexBuffer->getBufferSize());
	glBindVertexArray(0);
	shader->unbind();

	
}
void TexturedQuad::setAttributes(GLint*attributes,GLint*shadowAttributes){
	vertexBuffer->setVertexAttribute(attributes[ShaderAttributes::COORD3D]);
	textureBuffer->setVertexAttribute(attributes[ShaderAttributes::TEXCOORD2D]);


}


TexturedQuad::~TexturedQuad(void)
{
	delete vertexBuffer;
	delete textureBuffer;
}

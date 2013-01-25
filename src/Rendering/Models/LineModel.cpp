#include "LineModel.h"



LineModel::LineModel(void)
{
	lines = new std::vector<glm::vec3>();
	colors = new std::vector<glm::vec3>();
	lines->resize(1000);
	colors->resize(1000);
	numVertices = 0;


}

void LineModel::init(){
	glGenVertexArrays(1,&vao);
	lineBuffer = new Buffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,3,GL_FLOAT);
	colorBuffer = new Buffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,3,GL_FLOAT);
	
	shader = getResourceManager()->loadShader("lineShader");
	shader->bindAttribute(ShaderAttributes::COORD3D,"coord3d");
	shader->bindAttribute(ShaderAttributes::COLOR3D,"color3d");
	shader->bindUniform(ShaderUniforms::MVP,"mvp");
	setAttributes(shader->getAttributes());

	lineBuffer->init();
	colorBuffer->init();

	glBindVertexArray(vao);
	lineBuffer->bindTo(lineBuffer->getVertexAttribute());
	colorBuffer->bindTo(colorBuffer->getVertexAttribute());
	glBindVertexArray(0);


}

void LineModel::addLine(glm::vec3 &from ,glm::vec3 &to,glm::vec3 &color){

	if(lines->size() <= numVertices){
		lines->resize(lines->size()*2);
		colors->resize(lines->size()*2);
	}

	
	lines->data()[numVertices] = from;
	colors->data()[numVertices]  = color;
	numVertices++;
	lines->data()[numVertices]  = to;
	colors->data()[numVertices]  = color;
	numVertices++;
}
void LineModel::clearLines(){
	numVertices = 0;


}


void LineModel::bufferLines(){
	if(numVertices){
		
		lineBuffer->setData(lines->data(),sizeof(glm::vec3)*numVertices);
		colorBuffer->setData(colors->data(),sizeof(glm::vec3)*numVertices);

	}

}
void LineModel::render(Pipeline *pipeline){
	
	shader->bind();

	glm::mat4 model = pipeline->getTotalRotationTranslation()*getModelMatrix();
	glm::mat4 mvp = pipeline->getViewProjectionMatrix()*model;
	shader->setUniformMat4f(ShaderUniforms::MVP,glm::value_ptr(mvp));

	glBindVertexArray(vao);
	glDrawArrays(GL_LINES,0,lineBuffer->getBufferSize());
	glBindVertexArray(0);

	shader->unbind();

}
void LineModel::setAttributes(GLint*attributes,GLint*shadowAttributes){
	lineBuffer->setVertexAttribute(attributes[ShaderAttributes::COORD3D]);
	colorBuffer->setVertexAttribute(attributes[ShaderAttributes::COLOR3D]);


}

LineModel::~LineModel(void)
{
	
	delete lines;
	delete colors;

	delete lineBuffer;
	delete colorBuffer;


}

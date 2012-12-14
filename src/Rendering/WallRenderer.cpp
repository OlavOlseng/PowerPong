#include "WallRenderer.h"


WallRenderer::WallRenderer(std::vector<Wall*>*walls,Camera*cam)
{
	this->walls = walls;
	this->cam = cam;
	const char* vs = 
		"attribute vec4 coord4d;"
		"attribute vec4 color4d;"
		"uniform mat4 mvp;"
		"varying vec4 f_color;"
		"void main()"
		"{"
		"f_color = color4d;"
		"gl_Position = mvp*vec4(coord4d.xyz,1.0);"

		"}";
	const char*fs = 
		"varying vec4 f_color;"
		"void main(){"
		"gl_FragColor = f_color;"
		"}";
	this->program = compileShaders(vs,fs);
	attribute_coord4 = bindAttribute(program,"coord4d");
	attribute_color4 = bindAttribute(program,"color4d");
	unifrom_mvp = bindUniform(program,"mvp");


}
void WallRenderer::render(){
	
	glUseProgram(program);
	glEnable(GL_DEPTH_TEST);
	glEnableVertexAttribArray(attribute_coord4);
	glEnableVertexAttribArray(attribute_color4);
	
	for (int i = 0;i<walls->size();i++){
		Wall*wall = walls->at(i);
		glm::vec3 *pos = wall->getPosition();
		glm::mat4 model = glm::translate(glm::mat4(1.0),glm::vec3(pos->x,pos->y,pos->z));
		glm::mat4 mvp = cam->getProjXview()*model;
		Buffer*vertexBuffer = wall->getVertexBuffer();
		Buffer*colorBuffer= wall->getColorBuffer();

		glUniformMatrix4fv(unifrom_mvp,1,GL_FALSE,glm::value_ptr(mvp));

		glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer->getBufferHandle());
		glVertexAttribPointer(attribute_coord4, 4, GL_BYTE, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER,colorBuffer->getBufferHandle());
		glVertexAttribPointer(attribute_coord4, 4, GL_BYTE, GL_FALSE, 0, 0);
		//glBindBuffer(vertexBuffer->get
		glDrawArrays(GL_TRIANGLES,0,vertexBuffer->getBufferSize());
	}

		

}

WallRenderer::~WallRenderer(void)
{

}

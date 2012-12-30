#include "WallRenderer.h"


WallRenderer::WallRenderer(std::vector<gWall*>*walls,Camera*cam)
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
	this->program = ShaderUtil::compileShaders(vs,fs);
	attribute_coord4 = ShaderUtil::bindAttribute(program,"coord4d");
	attribute_color4 = ShaderUtil::bindAttribute(program,"color4d");
	unifrom_mvp = ShaderUtil::bindUniform(program,"mvp");
	

}
void WallRenderer::render(){
	
	glUseProgram(program);
	glEnable(GL_DEPTH_TEST);
	glEnableVertexAttribArray(attribute_coord4);
	glEnableVertexAttribArray(attribute_color4);

	int t = walls->size();
	for (int i = 0;i<walls->size();i++){
		gWall*wall = walls->at(i);
		glm::vec3 *pos = wall->getPosition();
		glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.0),glm::vec3(pos->x,pos->y,pos->z)),glm::vec3(1.0,1.0,1.0));
		glm::mat4 mvp = cam->getProjXview()*model;
		Buffer*vertexBuffer = wall->getVertexBuffer();
		Buffer*colorBuffer= wall->getColorBuffer();

		glUniformMatrix4fv(unifrom_mvp,1,GL_FALSE,glm::value_ptr(mvp));

		glBindBuffer(GL_ARRAY_BUFFER,vertexBuffer->getBufferHandle());
		glVertexAttribPointer(attribute_coord4, 4, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER,colorBuffer->getBufferHandle());
		glVertexAttribPointer(attribute_color4, 4, GL_FLOAT, GL_FALSE, 0, 0);
		
		glDrawArrays(GL_TRIANGLES,0,vertexBuffer->getBufferSize());
	}

	glDisableVertexAttribArray(attribute_coord4);
	glDisableVertexAttribArray(attribute_color4);
}

WallRenderer::~WallRenderer(void)
{

}

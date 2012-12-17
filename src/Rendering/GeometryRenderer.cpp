#include "GeometryRenderer.h"


GeometryRenderer::GeometryRenderer(Camera*cam,std::vector<Model*> * models)
{
	this->models = models;
	this->cam = cam;

	const char* vs = 
		"attribute vec3 coord3d;"
		"attribute vec3 normal3d;"
		"attribute vec2 texcoord2d;"
		"uniform mat4 mvp;"
		"varying vec3 f_normal;"
		"varying vec2 f_texcoord;"
		"void main()"
		"{"
		"f_normal = normal3d;"
		"f_texcoord = texcoord2d;"
		"gl_Position = mvp*vec4(coord3d.xyz,1.0);"
		"}";
	const char*fs = 
		"varying vec3 f_normal;"
		"varying vec2 f_texcoord;"
		"void main(){"
		"gl_FragColor = vec4(1.0,0.0,0.0,1.0);"
		"}";
	this->program = compileShaders(vs,fs);
	attribute_coord3d = bindAttribute(program,"coord3d");
	attriubte_normal3d = bindAttribute(program,"normal3d");
	attribute_texcoord = bindAttribute(program,"texcoord2d");
	unifrom_mvp = bindUniform(program,"mvp");
}


void GeometryRenderer::render(){


	glUseProgram(program);
	glEnable(GL_DEPTH_TEST);
	glEnableVertexAttribArray(attribute_coord3d);
	glEnableVertexAttribArray(attribute_texcoord);
	glEnableVertexAttribArray(attriubte_normal3d);

	
	for (int i = 0;i<models->size();i++){
		Model*model = models->at(i);
		glm::mat4 mvp = cam->getProjXview()*model->getModelMatrix();
		Buffer*vertexBuffer = model->getVertexBuffer();
		

		glUniformMatrix4fv(unifrom_mvp,1,GL_FALSE,glm::value_ptr(mvp));

		glBindBuffer(GL_ARRAY_BUFFER,model->getVertexBuffer()->getBufferHandle());
		glVertexAttribPointer(attribute_coord3d, 3, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,model->getElementBuffer()->getBufferHandle());
		
		glDrawElements(GL_TRIANGLES,model->getElementBuffer()->getBufferSize()/sizeof(GLushort),GL_UNSIGNED_SHORT,0);
	}

	glDisableVertexAttribArray(attribute_coord3d);
	glDisableVertexAttribArray(attribute_texcoord);
	glDisableVertexAttribArray(attriubte_normal3d);


}

GeometryRenderer::~GeometryRenderer(void)
{
}

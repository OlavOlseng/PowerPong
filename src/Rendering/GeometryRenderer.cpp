#include "GeometryRenderer.h"


GeometryRenderer::GeometryRenderer(Camera*cam,std::vector<Model*> * models)
{
	this->models = models;
	this->cam = cam;



	
	

}


void GeometryRenderer::registerModel(Model*model, Pipeline* pipeline){
	pipeline->useShader(model->getShader());
	Shader*shader = pipeline->getActiveShader();
	shader->bind();
	model->setAttributes(shader->getAttributeCoord3D(),shader->getAttributeNormal3D(),shader->getAttributeTexCoord2D());
	shader->unbind();

}
void GeometryRenderer::render(Pipeline *pipeline,Node*rootNode){
	pipeline->setView(cam->getView());
	pipeline->setProjection(cam->getProjection());
	
	glEnable(GL_DEPTH_TEST);

		rootNode->render(pipeline);
	
	
	
	


}

GeometryRenderer::~GeometryRenderer(void)
{
}

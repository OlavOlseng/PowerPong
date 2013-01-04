#include "GeometryRenderer.h"


GeometryRenderer::GeometryRenderer(Camera*cam,std::vector<Model*> * models)
{
	this->models = models;
	this->cam = cam;

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

#ifndef geometry_renderer_h
#define geomtry_renderer_h
#include "../camera/camera.h"
#include <GL\glew.h>
#include <GL\freeglut.h>;
#include <GL\GL.h>
#include <GL\GLU.h>
#include <vector>
#include "Model.h"
#include "shader_util.h"
#include "glm/gtc/type_ptr.hpp"
#include "Renderer.h"
#include "Shader.h"
#include "Pipeline.h"
#include "Node.h"
#include "ShaderList.h"


class GeometryRenderer:Renderer
{
public:
	GeometryRenderer(Camera*cam,std::vector<Model*> * models);
	~GeometryRenderer(void);
	void render(Pipeline *pipeline,Node * rootNode);
	void registerModel(Model*model, Pipeline* pipeline);

	
private:
	std::vector<Model*> * models;
	Camera* cam;

	


};

#endif
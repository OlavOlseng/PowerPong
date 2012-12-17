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
class GeometryRenderer:Renderer
{
public:
	GeometryRenderer(Camera*cam,std::vector<Model*> * models);
	~GeometryRenderer(void);
	void render();
	void registerModel(Model*model);

	GLuint getAttributeCoord3d();
	GLuint getAttributenormal3d();
	GLuint getAttributeTexCoord();
private:
	std::vector<Model*> * models;
	Camera* cam;

	GLint attribute_coord3d;
	GLint attribute_texcoord;
	GLint attriubte_normal3d;
	GLint program;
	GLint unifrom_mvp;

};

#endif
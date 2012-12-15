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
class GeometryRenderer
{
public:
	GeometryRenderer(Camera*cam,std::vector<Model*> * models);
	~GeometryRenderer(void);

	void render();
private:
	std::vector<Model*> * models;
	Camera* cam;

	GLuint attribute_coord3d;
	GLuint attribute_texcoord;
	GLuint attriubte_normal3d;
	GLuint program;
	GLuint unifrom_mvp;

};

#endif
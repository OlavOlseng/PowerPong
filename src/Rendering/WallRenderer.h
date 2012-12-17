#ifndef wall_renderer_h
#define wall_renderer_h
#include <vector>
#include "../Graphics/gWall.h"
#include <GL\glew.h>
#include <GL\freeglut.h>;
#include <GL\GL.h>
#include <GL\GLU.h>

#include "shader_util.h"
#include "glm/gtc/type_ptr.hpp"

#include "../camera/camera.h"

class WallRenderer
{
public:
	WallRenderer(std::vector<gWall*> *walls,Camera*cam);
	~WallRenderer(void);
	void render();
private:
	std::vector<gWall*> * walls;
	GLuint attribute_coord4;
	GLuint attribute_color4;
	GLuint unifrom_mvp;
	
	GLuint program;
	Camera*cam;


};

#endif
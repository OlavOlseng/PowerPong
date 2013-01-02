#ifndef gwall_h
#define gwall_h
#include "../Rendering/Buffer.h"
#include "gBlock.h"
#include <glm\glm.hpp>

#include <vector>
#include "../Rendering/Model.h"
#include "../Rendering/Pipeline.h"
class gWall:public Model
{
public:
	gWall(int blockScale,int lenght,glm::vec3 pos);
	~gWall(void);
	Buffer * getVertexBuffer();
	Buffer * getColorBuffer();
	void setBlock(int x,int width,glm::vec3 color);
	gBlock getBlock(int x);
	int getWidth();

	void setAttributes(GLint*attributes);
	void render(Pipeline *pipeline);
	GLuint* getVao() ;
	void setShader(int id);
	int getShader() ;

private:
	int blockScale;
	int width,height,depth;
	gBlock * blocks;
	Buffer vertexBuffer;
	Buffer colorBuffer;
	
	GLuint vao;
	int shaderName;
	
};

#endif
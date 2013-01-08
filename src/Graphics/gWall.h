#ifndef gwall_h
#define gwall_h
#include "../Rendering/Buffer.h"
#include "gBlock.h"
#include <glm\glm.hpp>

#include <vector>
#include "../Rendering/Model.h"
#include "../Rendering/Pipeline.h"
#include "../ResourceManager.h"
#include <memory>
class gWall:public Model
{
public:
	gWall(int blockScale,int lenght,glm::vec3 pos);
	~gWall(void);
	Buffer * getVertexBuffer();
	Buffer * getColorBuffer();
	Buffer * getTypeBuffer();
	Buffer * getNormalBuffer();

	void setBlock(int x,int width,glm::vec3 color);
	void setBlock(int x,int width,gBlock::BlockType type);
	gBlock getBlock(int x);
	int getWidth();
	void init();
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
	Buffer normalBuffer;
	Buffer typeBuffer;
	GLuint textureHandle;
	GLuint vao;

	int shaderName;
	
};

#endif
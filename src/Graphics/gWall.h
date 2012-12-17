#ifndef gwall_h
#define gwall_h
#include "../Rendering/Buffer.h"
#include "gBlock.h"
#include <glm\glm.hpp>
#include <vector>

class gWall
{
public:
	gWall(int blockScale,int lenght,glm::vec3 pos);
	~gWall(void);
	Buffer * getVertexBuffer();
	Buffer * getColorBuffer();
	glm::vec3 * getPosition();
	void setBlock(int x,int width,glm::vec3 color);
	gBlock getBlock(int x);
	int getWidth();

private:
	int blockScale;
	int width,height,depth;
	gBlock * blocks;
	Buffer vertexBuffer;
	Buffer colorBuffer;
	glm::vec3 pos;
	
};

#endif
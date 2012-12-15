#ifndef wall_h
#define wall_h
#include "../Rendering/Buffer.h"
#include "../Rendering/Block.h"
#include <glm\glm.hpp>
#include <vector>
class Wall
{
public:
	Wall(int blockScale,int lenght,glm::vec3 pos);
	~Wall(void);
	Buffer * getVertexBuffer();
	Buffer * getColorBuffer();
	glm::vec3 * getPosition();
	void setBlock(int x,int width,glm::vec3 color);
	Block getBlock(int x);
	int getWidth();
private:
	int blockScale;
	int width,height,depth;
	Block * blocks;
	Buffer vertexBuffer;
	Buffer colorBuffer;
	glm::vec3 pos;
	
};

#endif
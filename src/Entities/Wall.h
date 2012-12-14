#ifndef wall_h
#define wall_h
#include "../Rendering/Buffer.h"
#include "../Rendering/Block.h"
#include <glm\glm.hpp>
class Wall
{
public:
	Wall(int blockScale,int width,int height,glm::vec3 pos);
	~Wall(void);
	Buffer * getVertexBuffer();
	Buffer * getColorBuffer();
	glm::vec3 * getPosition();
	
private:
	int blockScale;
	int width,height;
	Block * blocks;
	Buffer vertexBuffer;
	Buffer colorBuffer;
	glm::vec3 pos;
	
};

#endif
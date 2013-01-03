#ifndef gBlock_h
#define gBlock_h
#include <glm\glm.hpp>

class gBlock
{
public:
	enum BlockType{NONE,GRASS,DIRT,ROCK};
	gBlock();
	~gBlock(void);
	int width;
	glm::vec3 color;
	bool empty;
	void set(int width,glm::vec3 color);
	void set(int width,BlockType type);
	BlockType type;

};

#endif
#ifndef block_h
#define block_h
#include <glm\glm.hpp>
class Block
{
public:
	Block();
	
	~Block(void);
	int width;
	glm::vec4 color;
	bool empty;
	void set(int width,glm::vec3 color);

};

#endif
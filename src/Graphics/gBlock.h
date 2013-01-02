#ifndef gBlock_h
#define gBlock_h
#include <glm\glm.hpp>

class gBlock
{
public:
	gBlock();
	~gBlock(void);
	int width;
	glm::vec3 color;
	bool empty;
	void set(int width,glm::vec3 color);

};

#endif
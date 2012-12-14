#ifndef block_h
#define block_h
#include <glm\glm.hpp>
class Block
{
public:
	Block();
	
	~Block(void);
	double width,height;
	glm::vec4 color;
	bool empty;
	void set(int width,int height,const glm::vec3 &color);

};

#endif
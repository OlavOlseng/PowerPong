#include "Wall.h"


Wall::Wall(double blockScale):vertexBuffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC)
{
	this->blockScale = blockScale;
}


Wall::~Wall(void)
{
}

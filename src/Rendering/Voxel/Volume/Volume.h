#ifndef VOLUME_H
#define VOLUME_H


#include <glm\glm.hpp>
#include <GL\glew.h>
#include <GL\freeglut.h>;
#include <GL\GL.h>
#include <GL\GLU.h>
#include <cstdint>
typedef glm::detail::tvec4<uint8_t> byte4;
typedef glm::detail::tvec4<float> float4;
typedef int BlockType;

class Volume
{
public:
	
	virtual void set(int x,int y,int z,BlockType type) = 0;
	virtual BlockType get(int x,int y,int z) = 0;
	virtual bool isInvisible() = 0;
	virtual bool isEmpty() = 0;
	virtual void setInvisible(bool invisible) = 0;
	virtual unsigned int getWidth() = 0;
	virtual unsigned int getHeight() = 0;
	virtual unsigned int getDepth() = 0;

	
};



#endif

#ifndef VOLUME_H
#define VOLUME_H


#include <glm\glm.hpp>

typedef glm::detail::tvec4<int> byte4;
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

};


#endif

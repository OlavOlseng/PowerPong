#ifndef ARRAY_VOLUME
#define ARRAY_VOLUME
#include "Volume.h"
class ArrayVolume : public Volume
{
public:
	ArrayVolume(int width,int height,int depth);
	~ArrayVolume(void);

	void set(int x,int y,int z,BlockType type);
	BlockType get(int x,int y,int z);
	bool isInvisible();
	bool isEmpty();
	void setInvisible(bool invisible);
	unsigned int getWidth();
	unsigned int getHeight();
	unsigned int getDepth();
private:
	inline int getIndex(int x,int y,int z);
	BlockType * blocks;
	int width,height,depth;
	int numBlocks;
	bool invisible;
	
};

#endif
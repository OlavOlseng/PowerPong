#ifndef LARGE_VOLUME_H
#define LARGE_VOLUME_H
#include "Volume.h"


template <typename T>
class LargeVolume:public Volume
{
public:

	LargeVolume(unsigned int width,unsigned int height ,unsigned int depth,unsigned int subWidth,unsigned int subHeight,unsigned int subDepth);

	

	 void set(int x,int y,int z,BlockType type);
	 BlockType get(int x,int y,int z);

	 bool isInvisible();
	 bool isEmpty();
	 void setInvisible(bool invisible);

	unsigned int getWidth();
	unsigned int getHeight();
	unsigned int getDepth();


	~LargeVolume(void);
private:
	Volume **subVolumes;
	inline unsigned int getIndex(int x,int y,int z);
	inline Volume * getSubVolume(int x,int y,int z);
	unsigned int height,width,depth;
	unsigned int numX,numY,numZ;
	unsigned int subWidth,subHeight,subDepth;

	bool invisible;
	
};



#include "LargeVolume.inl"

#endif
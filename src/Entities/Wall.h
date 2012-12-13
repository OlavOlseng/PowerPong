#ifndef wall_h
#define wall_h
#include "../Rendering/Buffer.h"

class Wall
{
public:
	Wall(double blockScale);
	~Wall(void);
	
private:
	double blockScale;

	Buffer vertexBuffer;

	
};

#endif
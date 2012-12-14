#ifndef wall_mesh_generator_h
#define wall_mesh_generator_h
#include "../Entities/Wall.h"
class WallMeshGenerator
{
public:
	WallMeshGenerator(void);
	void generateMeshFor(Wall wall);
	~WallMeshGenerator(void);
};

#endif
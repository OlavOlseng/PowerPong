#ifndef wall_mesh_generator_h
#define wall_mesh_generator_h
#include "../Volume/gWall.h"
#include <glm\core\_detail.hpp>
#include "../Volume/Volume.h"

class WallMeshGenerator
{
public:
	WallMeshGenerator(void);
	void generateMeshFor( gWall *wall);
	~WallMeshGenerator(void);
};

#endif
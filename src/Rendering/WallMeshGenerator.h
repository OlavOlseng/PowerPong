#ifndef wall_mesh_generator_h
#define wall_mesh_generator_h
#include "../Entities/Wall.h"
#include <glm\core\_detail.hpp>
typedef glm::detail::tvec4<GLbyte> byte4;

class WallMeshGenerator
{
public:
	WallMeshGenerator(void);
	void generateMeshFor( Wall *wall);
	~WallMeshGenerator(void);
};

#endif
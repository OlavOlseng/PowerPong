#ifndef VOXEL_RENDERER_H
#define VOXEL_RENDERER_H
#include "Model.h"
#include "../Voxel/SurfaceExtractors/VolumeSurface.h"
class VoxelRenderer:Model
{
public:
	VoxelRenderer(unsigned int numSurfacesX,unsigned int numSurfacesY,unsigned int numSurfacesZ);
	~VoxelRenderer(void);

	void render(Pipeline *pipeline);
	void setShader(int id);
	void setAttributes(GLint*attributes,GLint*shadowAttributes=nullptr);
	
	int getShader();

	void updateSurface(unsigned int x,unsigned int y, unsigned int z);
private:
	int shaderHandle;
	GLuint * surfaceVaos;
	VolumeSurface ** surfaces;
	unsigned int numSurfacesX;
	unsigned int numSurfacesY;
	unsigned int numSurfacesZ;

};

#endif
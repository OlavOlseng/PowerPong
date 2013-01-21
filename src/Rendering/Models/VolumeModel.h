#ifndef VOXEL_RENDERER_H
#define VOXEL_RENDERER_H
#include "Model.h"
#include "../Voxel/SurfaceExtractors/VolumeSurface.h"
class VolumeModel:public Model
{
public:
	VolumeModel(unsigned int numSurfacesX,unsigned int numSurfacesY,unsigned int numSurfacesZ);
	~VolumeModel(void);

	void render(Pipeline *pipeline);
	
	void setAttributes(GLint*attributes,GLint*shadowAttributes=nullptr);
	
	
	void setSurface(unsigned int x, unsigned int y, unsigned int z,VolumeSurface * surface);
	void updateSurface(unsigned int x,unsigned int y, unsigned int z);

	void init();
private:
	inline unsigned int getIndex(unsigned int x,unsigned int y,unsigned int z);
	
	GLuint * surfaceVaos;
	VolumeSurface ** surfaces;
	unsigned int numSurfacesX;
	unsigned int numSurfacesY;
	unsigned int numSurfacesZ;
	unsigned int numSurfaces;
	Shader * voxelShader;
	GLuint textureHandle;
	GLint vertexAttrib,normalAttrib;
};

#endif
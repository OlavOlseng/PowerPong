#ifndef VOXEL_RENDERER_H
#define VOXEL_RENDERER_H
#include "Model.h"
#include "../Voxel/SurfaceExtractors/VolumeSurface.h"
#include "../Util/TileAtlas.h"
class VolumeModel:public Model
{
public:
	VolumeModel(unsigned int numSurfacesX,unsigned int numSurfacesY,unsigned int numSurfacesZ,unsigned int surfaceWidth,unsigned int surfaceHeight,unsigned int surfaceDepth,std::shared_ptr<ResourceManager> resourceManager);
	~VolumeModel(void);

	void render(Pipeline *pipeline);
	
	void setAttributes(GLint*attributes,GLint*shadowAttributes=nullptr);
	
	
	void setSurface(unsigned int x, unsigned int y, unsigned int z,VolumeSurface * surface);
	void updateSurface(unsigned int x,unsigned int y, unsigned int z);

	void init(TileAtlas * tileAtlas);
private:
	inline unsigned int getIndex(unsigned int x,unsigned int y,unsigned int z);
	
	GLuint * surfaceVaos;
	VolumeSurface ** surfaces;
	unsigned int numSurfacesX,numSurfacesY,numSurfacesZ;
	unsigned int surfaceWidth,surfaceHeight,surfaceDepth;
	unsigned int numSurfaces;
	Shader * voxelShader;
	Texture * texture;
	TileAtlas * tileAtlas;
	GLint vertexAttrib,normalAttrib;
};

#endif
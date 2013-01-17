#include "VoxelRenderer.h"


VoxelRenderer::VoxelRenderer(unsigned int numSurfacesX,unsigned int numSurfacesY,unsigned int numSurfacesZ)
{

	unsigned int size = numSurfacesX*numSurfacesY*numSurfacesZ;
	surfaces = new VolumeSurface*[size];

	for(int i = 0;i<size;i++){
		surfaces[i] = nullptr;
	}

	


}

void VoxelRenderer::setShader(int id){

	this->shaderHandle = id;
}
void VoxelRenderer::setAttributes(GLint*attributes,GLint*shadowAttributes){


}

int VoxelRenderer::getShader(){
	return 0;

}

void VoxelRenderer::render(Pipeline *pipeline){


}

VoxelRenderer::~VoxelRenderer(void)
{
}

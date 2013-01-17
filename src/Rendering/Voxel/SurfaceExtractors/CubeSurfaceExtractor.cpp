#include "CubeSurfaceExtractor.h"


CubeSurfaceExtractor::CubeSurfaceExtractor(Volume * volume)
{
	this->volume = volume;
}



VolumeSurface * CubeSurfaceExtractor::extractSurface(unsigned int xStart,unsigned int yStart,unsigned int zStart,unsigned int width,unsigned int height,unsigned int depth){

	byte4 * vertices = new byte4[width*height*depth*36];
	byte4 * normals = new byte4[width*height*depth];

	VolumeSurface * surface = new VolumeSurface(width,height,depth,xStart,yStart,zStart);

	unsigned int xEnd,yEnd,zEnd;
	xEnd = xStart + width;
	yEnd = yStart + height;
	zEnd = zStart + depth;

	unsigned int i = 0;
	unsigned int globalX,globalY,globalZ;
	BlockType block;
	for (unsigned int z = 0; z<zEnd; z++) {
		
		for(unsigned int y= 0;y<yEnd;y++){

			for(unsigned int x = 0;x<xEnd;x++){

				block = volume->get(x,y,z);
				if(!block)
					continue;

				globalX = xStart + x;
				globalY = yStart + y;
				globalZ = zStart + z;

				//left face
				if(!volume->get(globalX-1,globalY,globalZ)){
					vertices[i++] = byte4(x,y,z,block);
					vertices[i++] = byte4(x,y,z+1,block);
					vertices[i++] = byte4(x,y+1,z+1,block);
             
					vertices[i++] = byte4(x,y,z,block);	
					vertices[i++] = byte4(x,y+1,z+1,block);
					vertices[i++] = byte4(x,y+1,z,block);	 
				}

				//right face
				if(!volume->get(globalX+1,globalY,globalZ)){
					vertices[i++] = byte4(x+1,y,z,block);
					vertices[i++] = byte4(x+1,y+1,z+1,block);
					vertices[i++] = byte4(x+1,y,z+1,block);

					vertices[i++] = byte4(x+1,y,z,block);
					vertices[i++] = byte4(x+1,y+1,z,block);
					vertices[i++] = byte4(x+1,y+1,z+1,block);
				}

				//backFace
				if(!volume->get(globalX,globalY,globalZ-1)){
					vertices[i++] = byte4(x,y,z,block);
					vertices[i++] = byte4(x+1,y+1,z,block);
					vertices[i++] = byte4(x+1,y,z,block);

					vertices[i++] = byte4(x,y,z,block);
					vertices[i++] = byte4(x,y+1,z,block);
					vertices[i++] = byte4(x+1,y+1,z,block);
                 }


				//frontFace
				if(!volume->get(globalX,globalY,globalZ+1)){
					vertices[i++] = byte4(x,y,z+1,block); 
					vertices[i++] = byte4(x+1,y,z+1,block);
					vertices[i++] = byte4(x+1,y+1,z+1,block);

	                vertices[i++] = byte4(x,y+1,z+1,block);
		            vertices[i++] = byte4(x,y,z+1,block);
			        vertices[i++] = byte4(x+1,y+1,z+1,block);
                }

				//bottomFace
				if(!volume->get(globalX,globalY-1,globalZ)){
					 vertices[i++] = byte4(x+1,y,z+1,block);
                     vertices[i++] = byte4(x,y,z,block);
					 vertices[i++] = byte4(x+1,y,z,block); 

					 vertices[i++] = byte4(x,y,z+1,block);
					 vertices[i++] = byte4(x,y,z,block);
					 vertices[i++] = byte4(x+1,y,z+1,block);

                }

				//topFace
				if(!volume->get(globalX,globalY+1,globalZ)){
					vertices[i++] = byte4(x+1,y+1,z+1,block);
					vertices[i++] = byte4(x+1,y+1,z,block);   
					vertices[i++] = byte4(x,y+1,z,block);
                        
					vertices[i++] = byte4(x,y+1,z+1,block);
					vertices[i++] = byte4(x+1,y+1,z+1,block);
					vertices[i++] = byte4(x,y+1,z,block);

				}


			}
		}
	}

	
	surface->setVertices(vertices,i);

	return surface;

}

CubeSurfaceExtractor::~CubeSurfaceExtractor(void)
{


}

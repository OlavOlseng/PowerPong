#include "CubeSurfaceExtractorWithByteNormals.h"


CubeSurfaceExtractorWithByteNormals::CubeSurfaceExtractorWithByteNormals(Volume * volume)
{

	this->volume = volume;

}


//Generates a surface with vertices
//The normals are representet by integers for 0-5 since a cube can only have 6 normals
//0: left 1:right 2:back 3:front 4:top 5:bottom
VolumeSurface * CubeSurfaceExtractorWithByteNormals::extractSurface(unsigned int xStart,unsigned int yStart,unsigned int zStart,unsigned int width,unsigned int height,unsigned int depth){

	byte4 * vertices = new byte4[width*height*depth*36];
	Normal * normals = new Normal[width*height*depth*36];

	VolumeSurface * surface = new VolumeSurface(width,height,depth,xStart,yStart,zStart);

	unsigned int xEnd,yEnd,zEnd;
	xEnd = xStart + width;
	yEnd = yStart + height;
	zEnd = zStart + depth;
	
	Normal left = 0,right = 1,back = 2,front = 3,top = 4,bottom = 5;


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
				
				if(globalX == 0 || !volume->get(globalX-1,globalY,globalZ)){
					normals[i] = left;
					vertices[i++] = byte4(x,y,z,block);
					normals[i] = left;
					vertices[i++] = byte4(x,y,z+1,block);
					normals[i] = left;
					vertices[i++] = byte4(x,y+1,z+1,block);
             
					normals[i] = left;
					vertices[i++] = byte4(x,y,z,block);	
					normals[i] = left;
					vertices[i++] = byte4(x,y+1,z+1,block);
					normals[i] = left;
					vertices[i++] = byte4(x,y+1,z,block);	 
				}

				//right face
				if(globalX == volume->getWidth()-1 || !volume->get(globalX+1,globalY,globalZ)){
					normals[i] = right;
					vertices[i++] = byte4(x+1,y,z,block);
					normals[i] = right;
					vertices[i++] = byte4(x+1,y+1,z+1,block);
					normals[i] = right;
					vertices[i++] = byte4(x+1,y,z+1,block);

					normals[i] = right;
					vertices[i++] = byte4(x+1,y,z,block);
					normals[i] = right;
					vertices[i++] = byte4(x+1,y+1,z,block);
					normals[i] = right;
					vertices[i++] = byte4(x+1,y+1,z+1,block);
				}

				//backFace
				if( globalZ == 0 || !volume->get(globalX,globalY,globalZ-1)){

					normals[i] = back;
					vertices[i++] = byte4(x,y,z,block);
					normals[i] = back;
					vertices[i++] = byte4(x+1,y+1,z,block);
					normals[i] = back;
					vertices[i++] = byte4(x+1,y,z,block);

					normals[i] = back;
					vertices[i++] = byte4(x,y,z,block);
					normals[i] = back;
					vertices[i++] = byte4(x,y+1,z,block);
					normals[i] = back;
					vertices[i++] = byte4(x+1,y+1,z,block);
                 }


				//frontFace
				if(globalZ == volume->getDepth()-1 || !volume->get(globalX,globalY,globalZ+1)){

					normals[i] = front;
					vertices[i++] = byte4(x,y,z+1,block); 
					normals[i] = front;
					vertices[i++] = byte4(x+1,y,z+1,block);
					normals[i] = front;
					vertices[i++] = byte4(x+1,y+1,z+1,block);

					normals[i] = front;
	                vertices[i++] = byte4(x,y+1,z+1,block);
					normals[i] = front;
		            vertices[i++] = byte4(x,y,z+1,block);
					normals[i] = front;
			        vertices[i++] = byte4(x+1,y+1,z+1,block);
                }

				//bottomFace
				if(globalY == 0 || !volume->get(globalX,globalY-1,globalZ)){

					 normals[i] = bottom;
					 vertices[i++] = byte4(x+1,y,z+1,block);
					 normals[i] = bottom;
                     vertices[i++] = byte4(x,y,z,block);
					 normals[i] = bottom;
					 vertices[i++] = byte4(x+1,y,z,block); 

					 normals[i] = bottom;
					 vertices[i++] = byte4(x,y,z+1,block);
					 normals[i] = bottom;
					 vertices[i++] = byte4(x,y,z,block);
					 normals[i] = bottom;
					 vertices[i++] = byte4(x+1,y,z+1,block);

                }

				//topFace
				if(globalY == volume->getHeight() -1 || !volume->get(globalX,globalY+1,globalZ)){

					
					normals[i] = top;
					vertices[i++] = byte4(x+1,y+1,z+1,block);
					normals[i] = top;
					vertices[i++] = byte4(x+1,y+1,z,block);  
					normals[i] = top;
					vertices[i++] = byte4(x,y+1,z,block);
                        
					normals[i] = top;
					vertices[i++] = byte4(x,y+1,z+1,block);
					normals[i] = top;
					vertices[i++] = byte4(x+1,y+1,z+1,block);
					normals[i] = top;
					vertices[i++] = byte4(x,y+1,z,block);

					
				}


			}
		}
	}

	
	surface->setVertices(vertices,i);
	surface->setNormals(normals,i);
	return surface;

}

CubeSurfaceExtractorWithByteNormals::~CubeSurfaceExtractorWithByteNormals(void)
{
}

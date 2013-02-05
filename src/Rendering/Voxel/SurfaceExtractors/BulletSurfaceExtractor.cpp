#include "BulletSurfaceExtractor.h"


BulletSurfaceExtractor::BulletSurfaceExtractor(Volume * volume)
{
	this->volume = volume;
}


btTriangleMesh *BulletSurfaceExtractor::extractBulletMesh(unsigned int xStart,unsigned int yStart,unsigned int zStart,unsigned int width,unsigned int height,unsigned int depth){

	
	

	 btTriangleMesh * mesh = new btTriangleMesh();

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
				if(globalX == 0 || !volume->get(globalX-1,globalY,globalZ)){
				
					mesh->addTriangle(btVector3(x,y,z),btVector3(x,y,z+1),btVector3(x,y+1,z+1),true);
					mesh->addTriangle(btVector3(x,y,z),btVector3(x,y+1,z+1),btVector3(x,y+1,z),true);    
					 
				}

				//right face
				if(globalX == volume->getWidth()-1 || !volume->get(globalX+1,globalY,globalZ)){

					mesh->addTriangle(btVector3(x+1,y,z),btVector3(x+1,y+1,z+1),btVector3(x+1,y,z+1),true);
					mesh->addTriangle(btVector3(x+1,y,z),btVector3(x+1,y+1,z),btVector3(x+1,y+1,z+1),true);   
				}
			
				//backFace
				if( globalZ == 0 || !volume->get(globalX,globalY,globalZ-1)){

					mesh->addTriangle(btVector3(x,y,z),btVector3(x+1,y+1,z),btVector3(x+1,y,z),true);
					mesh->addTriangle(btVector3(x,y,z),btVector3(x,y+1,z),btVector3(x+1,y+1,z),true);   

                 }


				//frontFace
				if(globalZ == volume->getDepth()-1 || !volume->get(globalX,globalY,globalZ+1)){

					mesh->addTriangle(btVector3(x,y,z+1),btVector3(x+1,y,z+1),btVector3(x+1,y+1,z+1),true);
					mesh->addTriangle(btVector3(x,y+1,z+1),btVector3(x,y,z+1),btVector3(x+1,y+1,z+1),true);   

                }
				
				//bottomFace
				if(globalY == 0 || !volume->get(globalX,globalY-1,globalZ)){


					mesh->addTriangle(btVector3(x+1,y,z+1),btVector3(x,y,z),btVector3(x+1,y,z),true);
					mesh->addTriangle(btVector3(x,y,z+1),btVector3(x,y,z),btVector3(x+1,y,z+1),true);   

	


                }

				//topFace
				if(globalY == volume->getHeight() -1 || !volume->get(globalX,globalY+1,globalZ)){

					mesh->addTriangle(btVector3(x+1,y+1,z+1),btVector3(x+1,y+1,z),btVector3(x,y+1,z),true);
					mesh->addTriangle(btVector3(x,y+1,z+1),btVector3(x+1,y+1,z+1),btVector3(x,y+1,z),true);   

					

                    

					
				}

			}
		}
	}

	return mesh;



}

BulletSurfaceExtractor::~BulletSurfaceExtractor(void)
{
}

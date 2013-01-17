#include "meshGenerator.h"

MeshGenerator::MeshGenerator(Terrain*terrain,SynchronizedQueue<BufferJob*> * bufferQueue)
{
	_terrain = terrain;
	_ambient_occlusion_enabled = false;
	_shared_unpack_memory = new byte4[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE*36];
    _shared_normal_memory = new byte4[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE*36];
    _shared_light_memory = new float[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE*36];
	_shared_occlusion_memory = new float[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE*36];
	_needsMeshUpdate = false;
	_bufferQueue = bufferQueue;
	boost::thread thread(boost::bind(&MeshGenerator::workerLoop,this));
	thread.detach();
}
void MeshGenerator::workerLoop(){
	while(1){

		Chunk*chunk = queue.pop();

			if(chunk){
				
				this->generateMeshForChunk(chunk);
			}
	
	}

}

MeshGenerator::~MeshGenerator()
{
}

void MeshGenerator::enableAmbientOcclusion(int numRays){
	_ambient_occlusion_enabled =true;
	
	_numrays = numRays;
	_rayCaster = new RayCaster(_numrays);
	_rayCaster->createRays();


}
void MeshGenerator::addChunkToQueue(Chunk*chunk){
	queue.push(chunk);

}

#include <boost\timer.hpp>

void MeshGenerator::generateMeshForChunk(Chunk*chunk){
	

	Block_Type adj[3][3][3];
	boost::timer timer;
	timer.restart();
    glm::vec3 pos = chunk->getPosition();
	int size = chunk->getSize();
	byte4*vertices = new byte4[CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE*36];
	byte4*normals = _shared_normal_memory;
	float*occlusion = _shared_occlusion_memory;
	Octree<uint8> cubes = chunk->getCubes();
	int *neighbors = new int[9];
    int i = 0;
    Block_Type type = 0;
    int x,y,z;

    float * face;
    float light = 0;
	int*collisions;
	int globalX,globalY,globalZ;
	int cx,cy,cz;
	float offset  = 0.0;
	int nCount = 0;
	int zStart,zEnd,xStart,xEnd,yStart,yEnd;

	if(pos.x >0) xStart = 0;
	else xStart = 1;
	if(pos.x < WORLD_SIZE_TRUE - CHUNK_SIZE) xEnd = 0;
	else xEnd = 1;

	if(pos.y >0) yStart = 0;
	else yStart = 1;
	if(pos.y < WORLD_SIZE_TRUE - CHUNK_SIZE) yEnd = 0;
	else yEnd = 1;

	if(pos.z >0) zStart = 0;
	else zStart = 1;
	if(pos.z < WORLD_SIZE_TRUE - CHUNK_SIZE) zEnd = 0;
	else zEnd = 1;



	for (z =zStart; z<size-zEnd; z++) {
		
		for(y= yStart;y<size-yEnd;y++){

			for(x= xStart;x<size-xEnd;x++){
               
				Block_Type block = cubes(x,y,z);
				if(!block)
					continue;
				
				type  = -block;
				globalX = pos.x + x;
				globalY = pos.y + y;
				globalZ = pos.z +z;

		
			
				nCount = 0;
				//left
				 if(!_terrain->getBlock(globalX-1,globalY,globalZ)){
					
					
					
					vertices[i++] = byte4(x,y,z,type);
                    vertices[i++] = byte4(x,y,z+1,type);
                    vertices[i++] = byte4(x,y+1,z+1,type);
             
					vertices[i++] = byte4(x,y,z,type);	
					vertices[i++] = byte4(x,y+1,z+1,type);
					vertices[i++] = byte4(x,y+1,z,type);

					 
				 }
				 //right
				if(!_terrain->getBlock(globalX+1,globalY,globalZ)){
					vertices[i++] = byte4(x+1,y,z,type);
                    vertices[i++] = byte4(x+1,y+1,z+1,type);
                    vertices[i++] = byte4(x+1,y,z+1,type);

                    vertices[i++] = byte4(x+1,y,z,type);
                    vertices[i++] = byte4(x+1,y+1,z,type);
                    vertices[i++] = byte4(x+1,y+1,z+1,type);

                   
            
                   }
				
				if( !_terrain->getBlock(globalX,globalY,globalZ-1)){
                //back

                 
                
					vertices[i++] = byte4(x,y,z,type);
					vertices[i++] = byte4(x+1,y+1,z,type);
					vertices[i++] = byte4(x+1,y,z,type);

             
					vertices[i++] = byte4(x,y,z,type);
					vertices[i++] = byte4(x,y+1,z,type);
					vertices[i++] = byte4(x+1,y+1,z,type);
                 
             
 
                 
               
                 }
                           
				if(!_terrain->getBlock(globalX,globalY,globalZ+1)){
                //front
			

                    
               
					vertices[i++] = byte4(x,y,z+1,type); 
					vertices[i++] = byte4(x+1,y,z+1,type);
					vertices[i++] = byte4(x+1,y+1,z+1,type);

               
              
	                vertices[i++] = byte4(x,y+1,z+1,type);
		            vertices[i++] = byte4(x,y,z+1,type);
			        vertices[i++] = byte4(x+1,y+1,z+1,type);
                    
          
             
                
                }





				   type *=-1;   
               
				 if(!_terrain->getBlock(globalX,globalY-1,globalZ)){
				        

                  
					 vertices[i++] = byte4(x+1,y,z+1,type);
                     vertices[i++] = byte4(x,y,z,type);
					 vertices[i++] = byte4(x+1,y,z,type); 
                      

					 vertices[i++] = byte4(x,y,z+1,type);
					 vertices[i++] = byte4(x,y,z,type);
					 vertices[i++] = byte4(x+1,y,z+1,type);
                     
                   
              
                } 
                   
         
                    //top
                


				   if(!_terrain->getBlock(globalX,globalY+1,globalZ)){

		

						  
						vertices[i++] = byte4(x+1,y+1,z+1,type);
						vertices[i++] = byte4(x+1,y+1,z,type);   
						vertices[i++] = byte4(x,y+1,z,type);
                        
						vertices[i++] = byte4(x,y+1,z+1,type);
						vertices[i++] = byte4(x+1,y+1,z+1,type);
						vertices[i++] = byte4(x,y+1,z,type);
                   
					}

				 }
			}
		}


if(i >0){


	
	chunk->setInvisible(false);
	_bufferQueue->push(new BufferJob(chunk->getVertexBuffer(),vertices,sizeof(byte4)*i,true));
}
else
	chunk->setInvisible(true);

printf("\n%f\n",timer.elapsed());
}



float MeshGenerator::getVertexHeight(int x,int y,int z,int side){
	float sum = y + side;
	int vertices = 1;
	//left 
	if(y+1< WORLD_SIZE_TRUE){
		Block_Type  block = _terrain->getBlock(x-1,y,z-1);
		sum +=y+side ;
		vertices++;
		if(block)
			 sum++;
	}
	//left
	
	
	
	return sum/vertices;
}

int MeshGenerator::interpolateBilinear(int x1,int y,int z1,FaceCorner corner){
	//x1 left x2 right
	//z1 back z2 front
	int x2;
	int z2;
	switch (corner)
	{
	case MeshGenerator::LEFT_UP:
		break;
	case MeshGenerator::LEFT_BOTTOM:
		break;
	case MeshGenerator::RIGHT_UP:
		break;
	case MeshGenerator::RIGHT_BOTTOM:
		break;

	}

	return -1;

}
//
//  terrain.cpp
//  openglbook
//
//  Created by Ellen Johansen on 7/6/12.
//  Copyright (c) 2012 Eirik Jakobsen. All rights reserved.
//

#include <iostream>
#include "terrain.h"
#include <hash_map>

Terrain::Terrain(){
    
    _chunks = new  Octree<Chunk*>(WORLD_SIZE);
    _chunks->setEmptyValue(EMPTY_CHUNK);
	  

}
Chunk*Terrain::getChunk(int x,int y,int z){
    
    return  _chunks->at(x, y, z);
}



void Terrain::setBlock(int x,int y,int z,Block_Type type){
    
    int chunkX = x/CHUNK_SIZE;
    int chunkY = y/CHUNK_SIZE;
    int chunkZ = z/CHUNK_SIZE;
    
    Chunk*chunk =  _chunks->at(chunkX,chunkY,chunkZ );
    if(chunk == EMPTY_CHUNK)
    {
        chunk = new Chunk(CHUNK_SIZE, glm::vec3(chunkX*CHUNK_SIZE,chunkY*CHUNK_SIZE,chunkZ*CHUNK_SIZE));
        _chunks->set(chunkX, chunkY, chunkZ, chunk);
    }
    
    chunk->set(x%CHUNK_SIZE, y%CHUNK_SIZE, z%CHUNK_SIZE, type);
    
    
}
 inline void  Terrain:: addLight(int x,int y,int z,Block_Face face,Face_Corner corner ,float strenght){
    
    if(strenght <0)
        return;
    
    int chunkX = x/CHUNK_SIZE;
    int chunkY = y/CHUNK_SIZE;
    int chunkZ = z/CHUNK_SIZE;
    
    Chunk*chunk =  _chunks->at(chunkX,chunkY,chunkZ );
    
    if(chunk != EMPTY_CHUNK)
    {
        if (!chunk->isAir()) {
            
            //chunk->addLight(x%CHUNK_SIZE, y%CHUNK_SIZE, z%CHUNK_SIZE,face,corner ,strenght);
        }   
        
    }
    


	

}

 /*
void Terrain:: setLight(int x,int y,int z,Block_Face face,Face_Corner corner ,float strenght){

    int chunkX = x/CHUNK_SIZE;
    int chunkY = y/CHUNK_SIZE;
    int chunkZ = z/CHUNK_SIZE;
    
    Chunk*chunk =  _chunks->at(chunkX,chunkY,chunkZ );
    
    if(chunk != EMPTY_CHUNK)
    {
        if (!chunk->isAir()) {
            chunk->setLight(x%CHUNK_SIZE, y%CHUNK_SIZE, z%CHUNK_SIZE, face,corner,strenght);
        }   
       
    }
    





}

struct Collision{

    int x,y,z;
    glm::vec3 ray;
    
    Collision(int x,int y,int z,glm::vec3 ray){
        this->x =x;
        this->y = y;
        this->z = z;
        this->ray = ray;
       
    }
    

    
    
    
};

struct Hasher:std::unary_function<Collision,std::size_t>{
    
    std::size_t operator()(const Collision &obj) const{
        std::size_t seed = 0;
        
        boost::hash_combine(seed, obj.x);
        boost::hash_combine(seed, obj.y);
        boost::hash_combine(seed, obj.z);

        return seed;
    }
    
};
struct Equal:std::binary_function<Collision,Collision, bool>
{
    
    bool operator()(const Collision &first, const Collision & other) const{
        
        return! first.x == other.x && first.y == other.y && first.z == other.z;
    }
};




void Terrain:: uppdateLight(Light*light){
	
    boost::unordered_set<Collision,Hasher,Equal> collisions;
    float x,y,z; 
    return ;
    std::vector<glm::vec3> rays;

    float step = 0.1;
    int bx,by,bz ;
    for ( x = -3.14/2; x<=3.14/2; x+= step) {
        
        for ( y = 0; y<=3.14*2; y+=step) {
            
            
        
            
            glm::vec3 lightPos = light->getPosition();
            
            
            
            glm::vec3 ray = glm::normalize( glm::vec3(cos(x)*cos(y),cos(x)*sin(y),sin(x)));
            
            
            for (float j = 1; j<20; j++) {
                
                bx = lightPos.x  + ray.x*j;
                by = lightPos.y + ray.y*j;
                bz = lightPos.z + ray.z*j;
                
                std::cout << "gekk";
                if(bx < WORLD_SIZE*CHUNK_SIZE && bx >=0 &&
                   by < WORLD_SIZE*CHUNK_SIZE && by >=0 &&
                   bz < WORLD_SIZE*CHUNK_SIZE && bz >=0 
                   
                   ){
                    
                   
                  
                   
                    
                    Block_Type  block = getBlock(bx, by, bz);
                    if (block == BLOCK_AIR)
                        continue;
                    
                    
                    if (!collisions.count(Collision(bx,by,bz,ray))) {
                        collisions.insert(Collision(bx,by,bz,ray));
                    }
                                         
                    break;
                                   
            }
            
            
            
            
            
            
            
            
            
        }
        
        
        }
    
    
    }
    
    
    boost::unordered_set<Collision,Hasher,Equal>::iterator it;
    
    float strenght = 1.0;
    for (it = collisions.begin(); it!=collisions.end(); it++) {
        printf("light x:%d y:%d z:%d \n",it->x,it->y,it->z);
        
        int   bx = it->x;
        int  by = it->y;
        int   bz = it->z;

        
        glm::vec3 ray =it->ray;;//= it->ray;
        float dot;
        //back
        //glm::vec3 ray =
       // setBlock(bx, by, bz,BLOCK_TYPE_ROCK);
        
       
        dot = glm::dot(glm::vec3(0.0,0.0,1.0), ray);
        
        addLight(bx, by, bz, FACE_BACK, FACE_TOP_LEFT, 1.0);
        addLight(bx, by, bz, FACE_LEFT, FACE_TOP_LEFT, 1.0);
        
        addLight(bx, by, bz, FACE_RIGHT, FACE_TOP_LEFT, 1.0);
        
        addLight(bx, by, bz, FACE_FRONT, FACE_TOP_LEFT, 1.0);
   
        if (dot >0) {
            
            addLight(bx, by, bz,FACE_BACK,FACE_TOP_LEFT,strenght);
            addLight(bx, by, bz,FACE_BACK,FACE_TOP_RIGHT, strenght);
            addLight(bx, by, bz,FACE_BACK,FACE_BOTTOM_LEFT, strenght);
            addLight(bx, by, bz,FACE_BACK,FACE_BOTTOM_RIGHT, strenght);
            
            
            
            
            
            
        }else{
            dot = glm::dot(glm::vec3(0.0,0.0,-1.0), ray);
            //front
            if (dot >0) {
                addLight(bx, by, bz,FACE_FRONT,FACE_TOP_LEFT, strenght);
                addLight(bx, by, bz,FACE_FRONT,FACE_TOP_RIGHT, strenght);
                addLight(bx, by, bz,FACE_FRONT,FACE_BOTTOM_LEFT, strenght);
                addLight(bx, by, bz,FACE_FRONT,FACE_BOTTOM_RIGHT, strenght);
                
            }
            
        }
        
        
        
        
        //left 
        dot = glm::dot(glm::vec3(1.0,0.0,0.0), ray);
        if (dot>0) {
            
            addLight(bx, by, bz,FACE_LEFT,FACE_TOP_LEFT, strenght);   
            addLight(bx, by, bz,FACE_LEFT,FACE_TOP_RIGHT, strenght);   
            addLight(bx, by, bz,FACE_LEFT,FACE_BOTTOM_LEFT, strenght); 
            addLight(bx, by, bz,FACE_LEFT,FACE_BOTTOM_RIGHT, strenght);   
            
            
            
        }else{
            
            //right
            dot = glm::dot(glm::vec3(-1.0,0.0,0.0), ray);
            
            if (dot >0) {
                //  addLight(bx, by, bz, 0.1);
                
                addLight(bx, by, bz,FACE_RIGHT,FACE_TOP_LEFT, strenght);   
                addLight(bx, by, bz,FACE_RIGHT,FACE_TOP_RIGHT, strenght);   
                addLight(bx, by, bz,FACE_RIGHT,FACE_BOTTOM_LEFT, strenght); 
                addLight(bx, by, bz,FACE_RIGHT,FACE_BOTTOM_RIGHT, strenght);   
                
                
            }
        }
        
        //up
        dot = glm::dot(glm::vec3(0.0,-1.0,0.0), ray);
        if (dot >0) {
            addLight(bx, by, bz,FACE_TOP,FACE_TOP_LEFT, strenght);   
            addLight(bx, by, bz,FACE_TOP,FACE_TOP_RIGHT, strenght);   
            addLight(bx, by, bz,FACE_TOP,FACE_BOTTOM_LEFT, strenght); 
            addLight(bx, by, bz,FACE_TOP,FACE_BOTTOM_RIGHT, strenght);   
            
            
        }else
        {
            //down
            dot = glm::dot(glm::vec3(0.0,1.0,0.0), ray);
            if (dot>0) {
                addLight(bx, by, bz,FACE_BOTTOM,FACE_TOP_LEFT, strenght);   
                addLight(bx, by, bz,FACE_BOTTOM,FACE_TOP_RIGHT, strenght);   
                addLight(bx, by, bz,FACE_BOTTOM,FACE_BOTTOM_LEFT, strenght); 
                addLight(bx, by, bz,FACE_BOTTOM,FACE_BOTTOM_RIGHT, strenght);   
                
                
            }
            
        }
        
        
        
        
        
        
    }

    
      
}
    
    





*/


float Terrain::getHeight(int x1,int y,int z1){




return -1;
}

 Block_Type Terrain::getBlock(int x,int y,int z){
    int chunkX = x/CHUNK_SIZE;
    int chunkY = y/CHUNK_SIZE;
    int chunkZ = z/CHUNK_SIZE;
    Chunk*chunk =  _chunks->at(chunkX,chunkY,chunkZ );
    if(chunk == EMPTY_CHUNK)
        return 0;
    
	
    return chunk->get(x%CHUNK_SIZE, y%CHUNK_SIZE, z%CHUNK_SIZE);
    

}

/*void Terrain::addStaticLight(Light * light){
    _lights.push_back(light);
    
    uppdateLight(light);
}*/
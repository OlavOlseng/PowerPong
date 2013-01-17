//
//  terrain.h
//  openglbook
//
//  Created by Ellen Johansen on 7/6/12.
//  Copyright (c) 2012 Eirik Jakobsen. All rights reserved.
//

#ifndef openglbook_terrain_h
#define openglbook_terrain_h
#include "base\base.h"
#include "../utils/octree/octree.h"
#include "../rendering/chunk.h"
#include "../constants/constants.h"
#include "../objects/light.h"

#include <vector>
#include <set>
#include <hash_set>
#include <boost\unordered\unordered_set.hpp>
#include "../utils/rayCastable.h"



class Terrain:public Base,RayCastable {
  
    
    private:
    std::vector<Light*> _lights;
    //todo: use a flat array for chunks
      Octree<Chunk*> *_chunks;
	

    
    void uppdateLights();
    void uppdateLight(Light*light);
    
public:
    Terrain();
    void addLight(int x,int y,int z,Block_Face face,Face_Corner corner ,float strenght);
    void setLight(int x,int y,int z,Block_Face face,Face_Corner corner, float strenght);
    void setBlock(int x,int y,int z,Block_Type type);
    float getHeight(int x,int y, int z);
    Chunk*getChunk(int x1,int y,int z1);
	 virtual Block_Type getBlock(int x,int y,int z) ;
    
    void addStaticLight(Light * light);
};


#endif

//
//  terrainRenderer.h
//  openglbook
//
//  Created by Ellen Johansen on 7/1/12.
//  Copyright (c) 2012 Eirik Jakobsen. All rights reserved.
//

#ifndef openglbook_terrainRenderer_h
#define openglbook_terrainRenderer_h
#include "../constants/constants.h"
#include "../utils/octree/octree.h"
#include "chunk.h"
#include "../glm/glm.hpp"
#include "../camera/camera.h"
#include "../glm/gtc/type_ptr.hpp"
#include "../utils/sphereFrustum.h"

#include "../objects/terrain.h"
#include "renderer.h"
#include "texture.h"
#include "../utils/shader_util.h"
#include "meshGenerator.h"
struct GlobalLightData{
	float sun;
};
class TerrainRenderer: public Renderer {
private:
   
	
    Texture * _textureAtlas;
	GlobalLightData lightData;
    GLuint _uniform_cameraDir;
    GLuint _uniform_cameraPos;
    GLuint _program;
    GLuint _unifrom_mvp;
    
    GLuint _uniform_lights;
	GLuint _uniform_sun;
    GLuint _uniform_lightpos;
    
    GLuint _attribute_coord4;
    GLuint _attribute_normal4;
    GLuint _attribute_light;
	GLuint _attribute_occlusion;
  
    glm::mat4 _view;
    glm::mat4 _proj;
    glm::mat4 _mvp;
    Terrain * _terrain;
	MeshGenerator* _mesh_generator;

public:
  
	TerrainRenderer(std::string binaryPath,Terrain*terrain, MeshGenerator*mesh_generator);
    void render();
};


#endif

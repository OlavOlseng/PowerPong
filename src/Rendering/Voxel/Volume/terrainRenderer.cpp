//
//  terrainRenderer.cpp
//  openglbook
//
//  Created by Ellen Johansen on 7/1/12.
//  Copyright (c) 2012 Eirik Jakobsen. All rights reserved.
//

#include <iostream>
#include "terrainRenderer.h"

#include <string.h>

TerrainRenderer::TerrainRenderer(std::string binaryPath,Terrain*terrain, MeshGenerator*mesh_generator){
    _terrain = terrain;
	_mesh_generator = mesh_generator;
	
    char * fs = readShaderFile(binaryPath.substr(0,binaryPath.find_last_of('\\')) +"\\terrainRenderer.frag");
    char * vs = readShaderFile((binaryPath.substr(0,binaryPath.find_last_of('\\')) +"\\terrainRenderer.vert"));
    


   
    
    
    _program = compileShaders(vs, fs);
    glUseProgram(_program);
    char*name = "coord4d";
   _attribute_coord4 = bindAttribute(_program, name);
    
    name = "normal4d";
    
    _attribute_normal4 = bindAttribute(_program, name);
    
    name = "light";
    _attribute_light = bindAttribute(_program, name);
    
    name = "cameraDir";
    _uniform_cameraDir = bindUnifrom(_program, name);
    name = "cameraPos";
    _uniform_cameraPos = bindUnifrom(_program, name);
    
    name = "sun";
	_uniform_sun = bindUnifrom(_program, name);
	
    name = "lightPos";
    
    _uniform_lightpos = bindUnifrom(_program, name);

    
    name = "lights";
    _uniform_lights  = bindUnifrom(_program, name);
    
	name = "occlusion";
	_attribute_occlusion = bindAttribute(_program,name);
	
   _textureAtlas = new Texture((binaryPath.substr(0,binaryPath.find_last_of('\\')) +"\\tileAtlas.png"));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST );
    
    glm::vec4 lights[2] = {
        
        glm::vec4(8.0,12.0,8.0,1.0),glm::vec4(8.0,5.0,8.0,1.0),
    };
    
    glUniform4fv(_uniform_lights, 4,  glm::value_ptr(lights[0]));
    
   
    
    name = "mvp";
  _unifrom_mvp = bindUnifrom(_program, name);



  
    
}

void TerrainRenderer::render(){
    
    int culls = 0;
  
    glUseProgram(_program);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureAtlas->getTextureId());
 
    
	glUniform1f(_uniform_sun,1.0);
    glUniform4fv(_uniform_lightpos, 4, glm::value_ptr(glm::vec4(8.0,5.0,8.0,1.0)));
    
    glEnableVertexAttribArray(_attribute_coord4);
    glEnableVertexAttribArray(_attribute_normal4);
    glEnableVertexAttribArray(_attribute_light);
	glEnableVertexAttribArray(_attribute_occlusion);
	static float rotation;
	rotation+=0.1;
	glm::mat4 testmodel = glm::rotate(glm::mat4(1.0),rotation,glm::vec3(0.0,1.0,0.0));

      SphereFrustum  frustum(SphereFrustum(_cam->getPos(), _cam->getDir(), 0.1, 150, 90.0, 800, 600));
    
    glm::vec3 pos;
    int x,z,y = 0;
    for ( z =0; z<WORLD_SIZE; z++) {
		for( y= 0;y<WORLD_HEIGHT;y++){
            for( x= 0;x<WORLD_SIZE;x++){

               pos = glm::vec3(x*CHUNK_SIZE*CUBE_SIZE,y*CHUNK_SIZE*CUBE_SIZE,z*CHUNK_SIZE*CUBE_SIZE);
                
               
                if(!frustum.hitTestRect(pos, CHUNK_SIZE)){
                    culls++;
                    continue;
                }
                
                Chunk * chunk = _terrain->getChunk(x, y, z);
               
                if(chunk == EMPTY_CHUNK){
                    culls++;
                    continue;

                    
                    
                }else{
					if (chunk->isAir() || chunk->isInvisible()) {
                        culls++;
                        continue;
                    }
                }
                

				/*if(!chunk->_isReady){
					chunk->updateMesh(_mesh_generator->_shared_unpack_memory,_mesh_generator->_shared_normal_memory,_mesh_generator->_shared_occlusion_memory,_mesh_generator->elements);
                
				}*/
                  glUniformMatrix4fv(_unifrom_mvp, 1, GL_FALSE, glm::value_ptr((*chunk).getMVP(_cam)));
				 
				  chunk->render(_attribute_coord4,_attribute_normal4,_attribute_light,_attribute_occlusion);
                
            }
        }
    }
    glDisableVertexAttribArray(_attribute_coord4);
    glDisableVertexAttribArray(_attribute_normal4);
    glDisableVertexAttribArray(_attribute_light);
	glDisableVertexAttribArray(_attribute_occlusion);
    
 // printf("%d chunks culled\n",culls);
        

}
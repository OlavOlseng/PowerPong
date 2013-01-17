//
//  chunk.cpp
//  openglbook
//
//  Created by Ellen Johansen on 7/1/12.
//  Copyright (c) 2012 Eirik Jakobsen. All rights reserved.
//

#include <iostream>
#include "chunk.h"

Chunk::Chunk(int size,glm::vec3 pos):_cubes(size){
    _size = size;
	_isInvisible = false;
	_isAir = true;
  
	_changed = false;
  
    _cubes.setEmptyValue(BLOCK_AIR);
    
    
	
    //36 vertices in a cube; 
    setPosition(glm::vec3(pos.x,pos.y,pos.z));
    
	_model = glm::scale(glm::translate(glm::mat4(1.0),glm::vec3(pos.x*CUBE_SIZE,pos.y*CUBE_SIZE,pos.z*CUBE_SIZE)),glm::vec3(CUBE_SIZE,CUBE_SIZE,CUBE_SIZE));
	
    _camIdentifier = -1;
	
	_occlusion_vbo = 0;
	_vertexBuffer = new Buffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC);

	
}
bool Chunk::isReady(){
	return _isReady;
}
int  Chunk::getSize(){
	return _size;
}
bool Chunk::isInvisible(){
	return _isInvisible;
}
Octree<uint8> Chunk::getCubes(){
	return _cubes;

}


void Chunk::set(int x,int y,int z,Block_Type type){
      _changed = true;
   
   
   
    _cubes.set(x, y, z,  type );
	_cubeCount++;
	_isAir = false;
}
Block_Type Chunk::get(int x,int y,int z){
    
    return _cubes(x,y,z);
}
glm::mat4 Chunk::getMVP(Camera*cam){
    
    if(_camIdentifier != cam->getIdentifier()){
        _mvp = cam->getProjXview()*_model;
        _camIdentifier = cam->getIdentifier();
    }
    return _mvp;
    
}
bool Chunk::isAir(){
    return _isAir;
}

bool Chunk::didChange(){
	return _changed;
}


Buffer* Chunk::getVertexBuffer(){

	return _vertexBuffer;
}

void Chunk::setInvisible(bool invisible){
	_isInvisible = invisible;
	
}

void Chunk::updateOcclusion(byte4*occlusion){

	
	



}

void Chunk::updateStaticLight(byte4*light){





}
void Chunk::updateMesh(byte4*vertices,byte4*normals,float*occlusion,int elements){
  
	/*
	*_elements = elements;
	
	glBindBuffer(GL_ARRAY_BUFFER,*_vertices_vbo);
	bufferStaticArray(GL_ARRAY_BUFFER, vertices, *_elements* sizeof(byte4));
	
    prepareBuffer(_normals_vbo, GL_ARRAY_BUFFER);
	bufferStaticArray(GL_ARRAY_BUFFER, normals, _elements* sizeof(byte4));

	prepareBuffer(_occlusion_vbo,GL_ARRAY_BUFFER);
	bufferStaticArray(GL_ARRAY_BUFFER,occlusion,_elements*sizeof(float));

    _changed = false;
	_isReady = true;
	*/
	
}


void Chunk::render(GLuint attribute_coord4d,GLuint attribute_normal4d,GLuint attribute_lights,GLuint attribute_occlusion){

	
	glBindBuffer(GL_ARRAY_BUFFER,_vertexBuffer->getBufferHandle());
	glVertexAttribPointer(attribute_coord4d, 4, GL_BYTE, GL_FALSE, 0, 0);

   /* glBindBuffer(GL_ARRAY_BUFFER, _normals_vbo);
    glVertexAttribPointer(attribute_normal4d, 4, GL_BYTE, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _occlusion_vbo);
	glVertexAttribPointer(attribute_occlusion, 1, GL_FLOAT, GL_FALSE, 0, 0);
    */

	glDrawArrays(GL_TRIANGLES, 0, _vertexBuffer->getBufferSize());
    

}
Chunk:: ~Chunk(){
   
    
   
    
}
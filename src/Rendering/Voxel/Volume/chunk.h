//
//  chunk.h
//  openglbook
//
//  Created by Ellen Johansen on 7/1/12.
//  Copyright (c) 2012 Eirik Jakobsen. All rights reserved.
//

#ifndef openglbook_chunk_h
#define openglbook_chunk_h

#include "../utils/octree/octree.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

#include "../camera/camera.h"
#include "../utils/shader_util.h"
#include "../objects/base/base.h"
#include "Buffer.h"
#include "../constants/constants.h"

typedef glm::detail::tvec4<GLbyte> byte4;
typedef glm::detail::tvec4<GLfloat> float4;


typedef uint8 Block_Face;
typedef uint8 Face_Corner;
class Chunk:public Base{
private:
    
    long _camIdentifier;
    glm::mat4 _model;
    glm::mat4 _mvp;
	Buffer* _vertexBuffer;
    GLuint _normals_vbo;
    GLuint _lights_vbo;
	GLuint _occlusion_vbo;
       
    Octree<uint8> _cubes;

    
    int _size;
    bool _isAir;
	bool _isInvisible;
    
    bool _changed;
	int _cubeCount;
    
    
public:
   // void setLight(int x,int y,int z,Block_Face face, Face_Corner corner,float val);
   // void addLight(int x,int y,int z,Block_Face face,Face_Corner corner,float val);
    
    void set(int x,int y,int z,Block_Type type);
    Block_Type get(int x,int y,int z);
	  bool _isReady;
    ~Chunk();
    Chunk(int size,glm::vec3 pos);
	void updateMesh(byte4*vertices,byte4*normals,float*occlusion,int elements);
	void updateOcclusion(byte4*occlusion);
	void updateStaticLight(byte4*light);
	int getSize();
	Octree<uint8> getCubes();
	void render(GLuint attribute_coord4d,GLuint attribute_normal4d,GLuint attribute_lights,GLuint attribute_occlusion);
    bool isAir();
	bool didChange();
	bool isInvisible();
	bool isReady();
	void setInvisible(bool invisible);
	void setVertexCount(int count);
	Buffer * getVertexBuffer();
    glm::mat4 getMVP(Camera * cam);
    
    
};

#endif

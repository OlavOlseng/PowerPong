//
//  camera.h
//  openglbook
//
//  Created by Ellen Johansen on 6/13/12.
//  Copyright (c) 2012 Voksenopplæringen. All rights reserved.
//

#ifndef openglbook_camera_h
#define openglbook_camera_h
#include  "glm/glm.hpp"

#include "glm/gtc/matrix_transform.hpp"

class Camera{
private:
    long _identifier;
    
    
protected:
    
    glm::mat4 _view;
    glm::mat4 _proj;
    glm::mat4 _projXview;
    glm::vec3 _pos;
    glm::vec3 _focus;
    glm::vec3 _dir;
    bool _didMove;
    
public:
    
    glm::vec3 getPos();
    glm::vec3 getDir();
    virtual glm::mat4 getProjectionMatrix();
	void setProjection(float width,float height);
    virtual glm::mat4 getViewMatrix();
    glm::mat4 getProjXview();
    
  virtual void setDir(glm::vec3 dir);
    
    Camera(float x,float y,float z,float lx,float ly,float lz,int width,int height);
    long getIdentifier();
    virtual void move (float dx,float dy,float dz);
    virtual void lookAt(float x,float y,float z);
    bool didMove();
    void setDidMove(bool value);
   virtual void tick();
};


#endif

//
//  camera.cpp
//  openglbook
//
//  Created by Ellen Johansen on 6/13/12.
//  Copyright (c) 2012 Voksenopplæringen. All rights reserved.
//

#include <iostream>
#include "camera.h"

Camera::Camera(float x,float y,float z,float lx,float ly,float lz,int width,int height){
    _pos = glm::vec3(x,y,z);
    _focus = glm::vec3(lx,ly,lz);
    _view = glm::lookAt(_pos, _focus, glm::vec3(0.0, 1, 0.0));
	
	setProjection(width,height);

    _projXview = _proj*_view;
    _didMove= false;
    _dir =glm::normalize( glm::vec3(lx-x,ly-y,lz-z));

    _identifier = 0;
   
    
}
void Camera::setDir(glm::vec3 dir){
    _dir = dir;
    _focus = getPos() + getDir()*(float)3.0;
    lookAt(_focus.x, _focus.y, _focus.z);

}
glm::vec3 Camera::getPos(){
    return _pos;
    }
glm::vec3 Camera::getDir(){
    return _dir;
}
glm::mat4 Camera::getViewMatrix(){
    return _view;
}

void Camera::move (float dx,float dy,float dz){    
    _pos.x = _pos.x + dx;
    _pos.y = _pos.y + dy;
    _pos.z = _pos.z + dz;
    
    _view= glm::lookAt(_pos, _focus, glm::vec3(0,1,0));
    _didMove = true;
    
    
}

void Camera::setProjection(float width,float height){


	_proj = glm::perspective(50.0, 1.0*width/height, 0.1, 300.0);

	setDidMove(true);
	tick();

}
glm::mat4 Camera::getProjectionMatrix(){

    return _proj;
}
glm::mat4 Camera::getProjXview(){
    return _projXview;

}
void Camera::lookAt(float x,float y,float z){
    
    _focus = glm::vec3(x,y,z);
    _view = glm::lookAt(_pos, _focus, glm::vec3(0.0,1.0,0.0));
    _didMove = true;
}
bool Camera::didMove(){
    return _didMove;
}
long Camera::getIdentifier(){
    return _identifier;
    }
void Camera::tick(){
    if (didMove()) {
        _projXview = _proj*_view;
        if(_identifier == LONG_MAX)
            _identifier = 0;
        else
            _identifier++;
    }
    _didMove = false;
}
void Camera::setDidMove(bool value){

    _didMove = value;
}

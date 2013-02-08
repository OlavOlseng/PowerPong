#include "TileAtlas.h"


TileAtlas::TileAtlas(std::string name,int numTilesX,int numTilesY,std::shared_ptr<ResourceManager> resourceManager)
{

	this->name = name;
	this->resourceManager = resourceManager;
	this->tileAtlas = resourceManager->loadTexture(name);
	this->tileAtlas->bind();
	this->tileAtlas->setMagFilter(Texture::Filter::NEAREST);
	this->tileAtlas->setMinFilter(Texture::Filter::NEAREST);

	this->tileAtlas = tileAtlas;
	this->numTilesX = numTilesX;
	this->numTilesY = numTilesY;
	this->stepSizeX = 1.0/(float)numTilesX;
	this->stepSizeY = 1.0/(float)numTilesY;
}



Texture * TileAtlas::getTexture(){

	return this->tileAtlas;

}
float TileAtlas::getStepSizeX(){

	return this->stepSizeX;
}
float TileAtlas::getStepSizeY(){
	
	return this->stepSizeY;
}
int TileAtlas::getNumTilesX(){

	return this->numTilesX;

}
int TileAtlas::getNumtilesY(){

	return this->numTilesY;
}

TileAtlas::~TileAtlas(void)
{

	resourceManager->freeTexture(name);
}

#ifndef TILE_ATLAS_H
#define TILE_ATLAS_H

#include "Texture.h"
#include "../Models/ResourceManager.h"
#include <string>
#include <memory>


class TileAtlas
{
public:
	TileAtlas(std::string name,int numTilesX,int numTilesY,std::shared_ptr<ResourceManager> resourceManager);
	~TileAtlas(void);


	Texture * getTexture();
	float getStepSizeX();
	float getStepSizeY();

	int getNumTilesX();
	int getNumtilesY();
private:
	Texture * tileAtlas;
	int numTilesX,numTilesY;
	float stepSizeX;
	float stepSizeY;
	std::shared_ptr<ResourceManager> resourceManager;
	std::string name;
	
};

#endif
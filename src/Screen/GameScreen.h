

#ifndef G_SCRN_H
#define G_SCRN_H



#include "Screen.h"
#include "../World/World.h"
#include "../Entities/Ball.h"
#include "../Rendering/Models/StaticModel.h"
#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\DefaultLogger.hpp>
#include <assimp\postprocess.h>
#include "../Rendering/Models/ResourceManager.h"
#include "../Rendering/camera/camera.h"
#include "../Entities/Block.h"
#include "../Rendering/Voxel/Volume/OctreeVolume.h"
#include "../Rendering/Models/VolumeModel.h"
#include "../Rendering/Voxel/SurfaceExtractors/CubeSurfaceExtractorWithByteNormals.h"
#include "../Rendering/Voxel/SurfaceExtractors/VolumeSurface.h"
#include "../Rendering/Models/LineModel.h"
#include <memory>

class GameScreen: public Screen
{
public:
	GameScreen(std::shared_ptr<ResourceManager> resourceManager,bool enableTest);
	~GameScreen(void);
	
	World* world;
	void reshape(int width, int height);
	virtual void update(double dt) override;
	virtual void render() override;

private:
	StaticModel * ballModel;
	VolumeModel * blockModel;
	Ball * ballEntity;
	Block * blockEntity;
	Node * rootNode;

	Camera*cam;
	//temp
	std::shared_ptr<ResourceManager> resourceManager;
	void test();

	Pipeline * pipeline;

};

#endif


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
#include "../Rendering/camera/FreeMovementCamera.h"
#include "../Entities/Block.h"
#include "../Rendering/Voxel/Volume/OctreeVolume.h"
#include "../Rendering/Models/VolumeModel.h"
#include "../Rendering/Voxel/SurfaceExtractors/CubeSurfaceExtractorWithByteNormals.h"
#include "../Rendering/Voxel/SurfaceExtractors/VolumeSurface.h"
#include "../Rendering/Models/LineModel.h"
#include <memory>
#include "../Input/InputHandler.h"
#include "../Rendering/Voxel/SurfaceExtractors/BulletSurfaceExtractor.h"
#include "../Entities/VolumeEntity.h"
#include "../Rendering/Util/FrameBuffer.h"
#include "../Rendering/Models/TexturedQuad.h"
#include "../Rendering/camera/Controller/UnconstrainedCameraController.h"
#include "../Input/KeyMap.h"
#include "../Rendering/camera/Controller/Behavior/KeyMovementBehaviour.h"
#include "../Rendering/camera/Controller/Behavior/MouseFPSBehaviour.h"
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
	InputHandler inputHandler;
	Ball * ballEntity;
	Block * blockEntity;
	Node * rootNode;

	FreeMovementCamera * cam;
	//temp
	std::shared_ptr<ResourceManager> resourceManager;
	void test();
	LineModel * crossHair;
	Pipeline * pipeline;
	Node * floorNode;

	UnconstrainedCameraController * cameraController;
	TexturedQuad * texturedQuad;

	TexturedQuad * translatedQuad;

	FrameBuffer * frameBuffer;
	



};

#endif
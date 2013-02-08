

#ifndef G_SCRN_H
#define G_SCRN_H



#include "../src/Rendering/Screen/Screen.h"
#include "../World/World.h"
#include "../Entities/Ball.h"

#include "../src/Rendering/Models/StaticModel.h"
#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\DefaultLogger.hpp>
#include <assimp\postprocess.h>
#include "../src/Rendering/Models/ResourceManager.h"
#include "../src/Rendering/camera/FreeMovementCamera.h"
#include "../Entities/Block.h"
#include "../src/Rendering/Voxel/Volume/OctreeVolume.h"
#include "../src/Rendering/Models/VolumeModel.h"
#include "../src/Rendering/Voxel/SurfaceExtractors/CubeSurfaceExtractorWithByteNormals.h"
#include "../src/Rendering/Voxel/SurfaceExtractors/VolumeSurface.h"
#include "../src/Rendering/Models/LineModel.h"
#include <memory>
#include "../src/Input/InputHandler.h"
#include "../src/Rendering/Voxel/SurfaceExtractors/BulletSurfaceExtractor.h"
#include "../Entities/VolumeEntity.h"
#include "../src/Rendering/Util/FrameBuffer.h"
#include "../src/Rendering/Models/TexturedQuad.h"
#include "../src/Rendering/camera/Controller/UnconstrainedCameraController.h"
#include "../src/Input/KeyMap.h"
#include "../src/Rendering/camera/Controller/Behavior/KeyMovementBehaviour.h"
#include "../src/Rendering/camera/Controller/Behavior/MouseFPSBehaviour.h"
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
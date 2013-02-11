

#ifndef G_SCRN_H
#define G_SCRN_H



#include <SGL\Rendering\Screen\Screen.h>
#include "../World/World.h"
#include "../Entities/Ball.h"

#include <SGL/Rendering/Models/StaticModel.h>
#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\DefaultLogger.hpp>
#include <assimp\postprocess.h>
#include <SGL/Rendering/Models/ResourceManager.h>
#include <SGL//Rendering/camera/FreeMovementCamera.h>
#include "../Entities/Block.h"
#include <SGL/Rendering/Voxel/Volume/OctreeVolume.h>
#include <SGL/Rendering/Models/VolumeModel.h>
#include <SGL/Rendering/Voxel/SurfaceExtractors/CubeSurfaceExtractorWithByteNormals.h>
#include <SGL/Rendering/Voxel/SurfaceExtractors/VolumeSurface.h>
#include <SGL/Rendering/Models/LineModel.h> 
#include <memory>
#include <SGL/Input/InputHandler.h>
#include <SGL/Rendering/Voxel/SurfaceExtractors/BulletSurfaceExtractor.h>
#include "../Entities/VolumeEntity.h"
#include <SGL/Rendering/Util/FrameBuffer.h>
#include <SGL/Rendering/Models/TexturedQuad.h>
#include <SGL/Rendering/camera/Controller/UnconstrainedCameraController.h>
#include <SGL/Input/KeyMap.h>
#include <SGL\Rendering\camera\Controller\Behavior\KeyMovementBehaviour.h>
#include <SGL/Rendering/camera/Controller/Behavior/MouseFPSBehaviour.h>
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
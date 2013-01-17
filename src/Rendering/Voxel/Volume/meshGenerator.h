#ifndef mesh_generator_h
#define mesh_generator_h
#include "../utils/SynchronizedQueue.h"
#include "../constants/constants.h"
#include "chunk.h"
#include "../objects/terrain.h"
#include <vector>
#include "../utils/rayCaster.h"
#include "../utils/octree/array2d.h"
#include <queue>
#include <boost/thread/thread.hpp>
#include "../rendering/BufferJob.h"

class MeshGenerator
{
public:
	
	MeshGenerator(Terrain*terrain,SynchronizedQueue<BufferJob*> * bufferQueue);
	~MeshGenerator();

	void addChunkToQueue(Chunk*chunk);
	void enableAmbientOcclusion( int numRays);
	
	int elements;
	byte4*_shared_unpack_memory;
    float*_shared_occlusion_memory;
    byte4*_shared_normal_memory;
	
	bool needsMeshUpdate();
private:
	enum FaceCorner {LEFT_UP,LEFT_BOTTOM,RIGHT_UP,RIGHT_BOTTOM};
	bool _needsMeshUpdate;
	void workerLoop();
	void generateMeshForChunk(Chunk*chunk);

	bool _ambient_occlusion_enabled;
	float*_rays;
	int _numrays;
	int interpolateBilinear(int x1,int y,int z1,FaceCorner corner);
	
	float getVertexHeight(int x,int y,int z,int side);
	Terrain*_terrain;


	RayCaster*_rayCaster;
	SynchronizedQueue<Chunk*> queue;
	SynchronizedQueue<BufferJob*> *_bufferQueue;
	
    float *_shared_light_memory;
	
};




#endif // !mesh_generator_h

#ifndef VOLUME_SURFACE_H
#define VOLUME_SURFACE_H

#include "../Volume/Volume.h"
#include "../../Shaders/Buffer.h"
class VolumeSurface
{
public:
	VolumeSurface(unsigned int width,unsigned int height,unsigned int depth,unsigned int x, unsigned int y, unsigned int z);
	~VolumeSurface(void);

	byte4 * getVertices();
	 byte4 * getNormals();

	void setVertices(byte4 * vertices,unsigned int numVertices);
	void setNormals(byte4 * normals,unsigned int numNormals);

	unsigned int getNumNormals();
	unsigned int getNumVertices();

	bool hasVertices();
	bool hasNormals();

	void bufferData();

private:
	// *vertices and *normals are very temporary
	// they are only valid when hasVertices and hasNormals are true
	//They may not be altered or deletet by the class
	byte4 * vertices;
	byte4 * normals;

	unsigned int numVertices;
	unsigned int numNormals;

	bool m_hasVertices;
	bool m_hasNormals;

	const unsigned int width,height,depth;
	const unsigned int x,y,z;

	Buffer * vertexBuffer;
	Buffer * normalBuffer;


};

#endif
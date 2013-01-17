#include "VolumeSurface.h"


VolumeSurface::VolumeSurface(unsigned int width,unsigned int height,unsigned int depth,unsigned int x, unsigned int y, unsigned int z):
	width(width),height(height),depth(depth),x(x),y(y),z(z)
{
	m_hasVertices = false;
	m_hasNormals = false;
	vertexBuffer = new Buffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,4,GL_BYTE);
	normalBuffer = new Buffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,4,GL_BYTE);

}


byte4 * VolumeSurface::getVertices(){
	
	return this->vertices;
}
byte4 * VolumeSurface::getNormals(){

	return this->normals;
}

void VolumeSurface::setVertices(byte4 * vertices,unsigned int numVertices){

	this->vertices = vertices;
	this->m_hasVertices = true;
	this->numVertices = numVertices;
}
void VolumeSurface::setNormals(byte4 * normals,unsigned int numNormals){

	this->normals = normals;
	this->m_hasNormals = true;
	this->numNormals = numNormals;

}

void VolumeSurface::bufferData(){

	if(m_hasVertices)
		vertexBuffer->setData(vertices,sizeof(byte4)*numVertices);
	if(m_hasNormals)
		normalBuffer->setData(normals,sizeof(byte4)*numNormals);

}

unsigned int VolumeSurface::getNumNormals(){

	return this->numNormals;

}
unsigned int VolumeSurface::getNumVertices(){

	return this->numVertices;
}

bool VolumeSurface::hasVertices(){

	return this->m_hasVertices;

}
bool VolumeSurface::hasNormals(){

	return this->m_hasNormals;
}


VolumeSurface::~VolumeSurface(void)
{
}

#include "VolumeSurface.h"


VolumeSurface::VolumeSurface(unsigned int width,unsigned int height,unsigned int depth,unsigned int x, unsigned int y, unsigned int z):
	width(width),height(height),depth(depth),x(x),y(y),z(z)
{
	m_hasVertices = false;
	m_hasNormals = false;
	vertexBuffer = new Buffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,4,GL_BYTE);
	normalBuffer = new Buffer(Buffer::BufferType::ARRAY_BUFFER,Buffer::BufferDrawMode::STATIC,1,GL_BYTE);

}


byte4 * VolumeSurface::getVertices(){
	
	return this->vertices;
}
Normal * VolumeSurface::getNormals(){

	return this->normals;
}

void VolumeSurface::setVertices(byte4 * vertices,unsigned int numVertices){

	this->vertices = vertices;
	this->m_hasVertices = true;
	this->numVertices = numVertices;
}
void VolumeSurface::setNormals(Normal * normals,unsigned int numNormals){

	this->normals = normals;
	this->m_hasNormals = true;
	this->numNormals = numNormals;

}

Buffer * VolumeSurface::getVertexBuffer(){

	return this->vertexBuffer;
}
Buffer * VolumeSurface::getNormalBuffer(){

	return this->normalBuffer;

}

void VolumeSurface::bufferData(){

	if(m_hasVertices){
		vertexBuffer->setData(this->vertices,sizeof(byte4)*numVertices);
		delete[] vertices;
		m_hasVertices = false;
		this->numVertices = 0;
	}

	if(m_hasNormals){
		normalBuffer->setData(this->normals,sizeof(Normal)*numNormals);
		delete[] normals;
		m_hasNormals = false;
		this->numNormals = 0;;
	}

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
	delete vertexBuffer;
	delete normalBuffer;
}

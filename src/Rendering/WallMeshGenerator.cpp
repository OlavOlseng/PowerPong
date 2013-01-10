#include "WallMeshGenerator.h"
#include <glm\core\_detail.hpp>

WallMeshGenerator::WallMeshGenerator(void)
{
}

void WallMeshGenerator::generateMeshFor(gWall *wall){

	glm::vec3 *vertices = new glm::vec3[wall->getWidth()*36];
	glm::vec3 *normals = new glm::vec3[wall->getWidth()*36];
	glm::vec3*colors = new glm::vec3[wall->getWidth()*36];
	float*type = new float[wall->getWidth()*36];
	glm::vec3 left = glm::vec3(-1.0,0.0,0.0);
	glm::vec3 right = glm::vec3(1.0,0.0,0.0);
	glm::vec3 back = glm::vec3(0.0,0.0,-1.0);
	glm::vec3 front = glm::vec3(0.0,0.0,1.0);
	glm::vec3 up = glm::vec3(0.0,1.0,0.0);
	glm::vec3 down =glm::vec3(0.0,-1.0,0.0);
	glm::vec3 normal;
	int i = 0,j=0,ii=0,jj = 0;
	int x = 0;

	for( x= 0;x<wall->getWidth();x++){
		gBlock block = wall->getBlock(x);
		
		if(block.empty)
			continue;
			
		normal = left;
		//left	
		vertices[i++] = glm::vec3(x,0,0);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x,0,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x,0+1,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
             
		vertices[i++] = glm::vec3(x,0,0);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x,0+1,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x,0+1,0);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
	 
		normal = right;
		//right	
		vertices[i++] = glm::vec3(x+1,0,0);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x+1,0+1,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x+1,0,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;

		vertices[i++] = glm::vec3(x+1,0,0);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x+1,0+1,0);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x+1,0+1,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
	
		normal = back;
		//back       
		vertices[i++] = glm::vec3(x,0,0);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x+1,0+1,0);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x+1,0,0);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;

             
		vertices[i++] = glm::vec3(x,0,0);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x,0+1,0);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x+1,0+1,0);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
	
		normal = front;
		//front       
		vertices[i++] = glm::vec3(x,0,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal; 
		vertices[i++] = glm::vec3(x+1,0,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x+1,0+1,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;

               
              
		vertices[i++] = glm::vec3(x,0+1,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x,0,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x+1,0+1,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;normals[jj++] = normal;

		normal = down;
        //bot   
		vertices[i++] = glm::vec3(x+1,0,0+1);colors[j++] = block.color;type[ii++] = -(float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x,0,0);colors[j++] = block.color;type[ii++] = -(float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x+1,0,0);colors[j++] = block.color;type[ii++] = -(float)block.type;normals[jj++] = normal; 
                      

		vertices[i++] = glm::vec3(x,0,0+1);colors[j++] = block.color;type[ii++] = -(float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x,0,0);colors[j++] = block.color;type[ii++] = -(float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x+1,0,0+1);colors[j++] = block.color;type[ii++] = -(float)block.type;normals[jj++] = normal;

		normal = up;
		//top		  
		vertices[i++] = glm::vec3(x+1,0+1,0+1);colors[j++] = block.color;type[ii++] = -(float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x+1,0+1,0);colors[j++] = block.color;type[ii++] =-(float)block.type;normals[jj++] = normal;   
		vertices[i++] = glm::vec3(x,0+1,0);colors[j++] = block.color;type[ii++] = -(float)block.type;normals[jj++] = normal;
                        
		vertices[i++] = glm::vec3(x,0+1,0+1);colors[j++] = block.color;type[ii++] = -(float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x+1,0+1,0+1);colors[j++] = block.color;type[ii++] = -(float)block.type;normals[jj++] = normal;
		vertices[i++] = glm::vec3(x,0+1,0);colors[j++] = block.color;type[ii++] = -(float)block.type;normals[jj++] = normal;
	}
	
	

	GLuint * vao = wall->getVao();
	wall->getVertexBuffer()->setData(vertices,sizeof(glm::vec3)*i);
	wall->getColorBuffer()->setData(colors,sizeof(glm::vec3)*i);
	wall->getTypeBuffer()->setData(type,sizeof(float)*i);
	wall->getNormalBuffer()->setData(normals,sizeof(glm::vec3)*jj);
	Buffer*vertBuffer = wall->getVertexBuffer();
	Buffer*normalBuffer = wall->getNormalBuffer();
	Buffer*typeBuffer = wall->getTypeBuffer();
	Buffer*colorBuffer = wall->getColorBuffer();
	glBindVertexArray(*vao);
	vertBuffer->bindTo(vertBuffer->getVertexAttribute());
	normalBuffer->bindTo(normalBuffer->getVertexAttribute());
	colorBuffer->bindTo(colorBuffer->getVertexAttribute());
	typeBuffer->bindTo(typeBuffer->getVertexAttribute());
	glBindVertexArray(0);
}
WallMeshGenerator::~WallMeshGenerator(void)
{
}

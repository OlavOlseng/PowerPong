#include "WallMeshGenerator.h"
#include <glm\core\_detail.hpp>

WallMeshGenerator::WallMeshGenerator(void)
{
}

void WallMeshGenerator::generateMeshFor(gWall *wall){

	glm::vec3 *vertices = new glm::vec3[wall->getWidth()*36];
	glm::vec3*colors = new glm::vec3[wall->getWidth()*36];
	float*type = new float[wall->getWidth()*36];

	int i = 0,j=0,ii=0;
	int x = 0;

	for( x= 0;x<wall->getWidth();x++){
		gBlock block = wall->getBlock(x);
		
		if(block.empty)
			continue;
			
		//left	
		vertices[i++] = glm::vec3(x,0,0);colors[j++] = block.color;type[ii++] = (float)block.type;
		vertices[i++] = glm::vec3(x,0,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;
		vertices[i++] = glm::vec3(x,0+1,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;
             
		vertices[i++] = glm::vec3(x,0,0);colors[j++] = block.color;type[ii++] = (float)block.type;
		vertices[i++] = glm::vec3(x,0+1,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;
		vertices[i++] = glm::vec3(x,0+1,0);colors[j++] = block.color;type[ii++] = (float)block.type;
	 
		//right	
		vertices[i++] = glm::vec3(x+1,0,0);colors[j++] = block.color;type[ii++] = (float)block.type;
		vertices[i++] = glm::vec3(x+1,0+1,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;
		vertices[i++] = glm::vec3(x+1,0,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;

		vertices[i++] = glm::vec3(x+1,0,0);colors[j++] = block.color;type[ii++] = (float)block.type;
		vertices[i++] = glm::vec3(x+1,0+1,0);colors[j++] = block.color;type[ii++] = (float)block.type;
		vertices[i++] = glm::vec3(x+1,0+1,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;
	
		//back       
		vertices[i++] = glm::vec3(x,0,0);colors[j++] = block.color;type[ii++] = (float)block.type;
		vertices[i++] = glm::vec3(x+1,0+1,0);colors[j++] = block.color;type[ii++] = (float)block.type;
		vertices[i++] = glm::vec3(x+1,0,0);colors[j++] = block.color;type[ii++] = (float)block.type;

             
		vertices[i++] = glm::vec3(x,0,0);colors[j++] = block.color;type[ii++] = (float)block.type;
		vertices[i++] = glm::vec3(x,0+1,0);colors[j++] = block.color;type[ii++] = (float)block.type;
		vertices[i++] = glm::vec3(x+1,0+1,0);colors[j++] = block.color;type[ii++] = (float)block.type;
	
		//front       
		vertices[i++] = glm::vec3(x,0,0+1);colors[j++] = block.color;type[ii++] = (float)block.type; 
		vertices[i++] = glm::vec3(x+1,0,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;
		vertices[i++] = glm::vec3(x+1,0+1,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;

               
              
		vertices[i++] = glm::vec3(x,0+1,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;
		vertices[i++] = glm::vec3(x,0,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;
		vertices[i++] = glm::vec3(x+1,0+1,0+1);colors[j++] = block.color;type[ii++] = (float)block.type;

        //bot   
		vertices[i++] = glm::vec3(x+1,0,0+1);colors[j++] = block.color;type[ii++] = -(float)block.type;
		vertices[i++] = glm::vec3(x,0,0);colors[j++] = block.color;type[ii++] = -(float)block.type;
		vertices[i++] = glm::vec3(x+1,0,0);colors[j++] = block.color;type[ii++] = -(float)block.type; 
                      

		vertices[i++] = glm::vec3(x,0,0+1);colors[j++] = block.color;type[ii++] = -(float)block.type;
		vertices[i++] = glm::vec3(x,0,0);colors[j++] = block.color;type[ii++] = -(float)block.type;
		vertices[i++] = glm::vec3(x+1,0,0+1);colors[j++] = block.color;type[ii++] = -(float)block.type;

		//top		  
		vertices[i++] = glm::vec3(x+1,0+1,0+1);colors[j++] = block.color;type[ii++] = -(float)block.type;
		vertices[i++] = glm::vec3(x+1,0+1,0);colors[j++] = block.color;type[ii++] =-(float)block.type;   
		vertices[i++] = glm::vec3(x,0+1,0);colors[j++] = block.color;type[ii++] = -(float)block.type;
                        
		vertices[i++] = glm::vec3(x,0+1,0+1);colors[j++] = block.color;type[ii++] = -(float)block.type;
		vertices[i++] = glm::vec3(x+1,0+1,0+1);colors[j++] = block.color;type[ii++] = -(float)block.type;
		vertices[i++] = glm::vec3(x,0+1,0);colors[j++] = block.color;type[ii++] = -(float)block.type;
	}
	
	

	GLuint * vao = wall->getVao();
	glBindVertexArray(*vao);
	wall->getVertexBuffer()->setData(vertices,sizeof(glm::vec3)*i);

	wall->getColorBuffer()->setData(colors,sizeof(glm::vec3)*i);
	wall->getTypeBuffer()->setData(type,sizeof(float)*i);
	glBindVertexArray(0);
}
WallMeshGenerator::~WallMeshGenerator(void)
{
}

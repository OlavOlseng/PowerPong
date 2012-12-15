#include "WallMeshGenerator.h"
#include <glm\core\_detail.hpp>

WallMeshGenerator::WallMeshGenerator(void)
{
}

void WallMeshGenerator::generateMeshFor(Wall *wall){

	glm::vec4 *vertices = new glm::vec4[wall->getWidth()*36];
	glm::vec4*colors = new glm::vec4[wall->getWidth()*36];
	int i = 0;
	int x = 0;

	for( x= 0;x<wall->getWidth();x++){
		Block block = wall->getBlock(x);
		
		if(block.empty)
			continue;
			
		//left	
		vertices[i++] = glm::vec4(x,0,0,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x,0,0+1,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x,0+1,0+1,1);colors[i] = block.color;
             
		vertices[i++] = glm::vec4(x,0,0,1);colors[i] = block.color;	
		vertices[i++] = glm::vec4(x,0+1,0+1,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x,0+1,0,1);colors[i] = block.color;
	 
		//right	
		vertices[i++] = glm::vec4(x+1,0,0,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x+1,0+1,0+1,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x+1,0,0+1,1);colors[i] = block.color;

		vertices[i++] = glm::vec4(x+1,0,0,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x+1,0+1,0,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x+1,0+1,0+1,1);colors[i] = block.color;
	
		//back       
		vertices[i++] = glm::vec4(x,0,0,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x+1,0+1,0,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x+1,0,0,1);colors[i] = block.color;

             
		vertices[i++] = glm::vec4(x,0,0,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x,0+1,0,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x+1,0+1,0,1);colors[i] = block.color;
	
		//front       
		vertices[i++] = glm::vec4(x,0,0+1,1);colors[i] = block.color; 
		vertices[i++] = glm::vec4(x+1,0,0+1,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x+1,0+1,0+1,1);colors[i] = block.color;

               
              
		vertices[i++] = glm::vec4(x,0+1,0+1,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x,0,0+1,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x+1,0+1,0+1,1);colors[i] = block.color;

        //bot   
		vertices[i++] = glm::vec4(x+1,0,0+1,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x,0,0,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x+1,0,0,1);colors[i] = block.color; 
                      

		vertices[i++] = glm::vec4(x,0,0+1,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x,0,0,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x+1,0,0+1,1);colors[i] = block.color;

		//top		  
		vertices[i++] = glm::vec4(x+1,0+1,0+1,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x+1,0+1,0,1);colors[i] = block.color;   
		vertices[i++] = glm::vec4(x,0+1,0,1);colors[i] = block.color;
                        
		vertices[i++] = glm::vec4(x,0+1,0+1,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x+1,0+1,0+1,1);colors[i] = block.color;
		vertices[i++] = glm::vec4(x,0+1,0,1);colors[i] = block.color;
                   
                  
				

	}
	

	wall->getVertexBuffer()->setData(vertices,sizeof(glm::vec4)*i);

	
	wall->getColorBuffer()->setData(colors,sizeof(glm::vec4)*i);
	

}
WallMeshGenerator::~WallMeshGenerator(void)
{
}

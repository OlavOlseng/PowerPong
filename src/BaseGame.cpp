#include "BaseGame.h"





BaseGame::BaseGame()
{	
	
	
}

void BaseGame::init(std::string windowTitle,int width,int height){
	

	glfwInit();
	
	glfwOpenWindow(width,height,8,8,8,8,16,0,GLFW_WINDOW);
	glfwSetWindowTitle(windowTitle.c_str());
	
	//glfwSwapInterval(0);
	
	GLenum err = glewInit();
	if(err !=GLEW_OK){
		printf("Glew init failed: %s \n",glewGetErrorString(err));
		std::system("PAUSE");
		return;
	}


	this->width = width;
	this->height = height;
	



	if(!GLEW_VERSION_3_0){
		printf("Error opengl 3.0 not supported");
		std::system("PAUSE");
		glfwTerminate();
		return;
	}
	
	glfwSetTime(0);

	lastTime = glfwGetTime();
	
	
	setup();
	
	enterMainLoop();

	
}



void BaseGame::enterMainLoop(){

	double time;
	
	int glfw_width,glfw_height;
	while(glfwGetWindowParam(GLFW_OPENED)){
		
		glfwGetWindowSize(&glfw_width,&glfw_height);
		if(this->width != glfw_width || this->height != glfw_height){
			this->width = glfw_width;
			this->height = glfw_height;
			this->reshape(this->width,this->height);
		}

		time = glfwGetTime()-lastTime;
		
		update(time);
		lastTime = glfwGetTime();
		draw();
		

	}


}

void BaseGame::swapBuffers(){
	glfwSwapBuffers();
}
BaseGame::~BaseGame(void)
{
}

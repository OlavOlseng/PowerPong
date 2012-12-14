#include "BaseGame.h"





BaseGame::BaseGame()
{	
		
	
}

void BaseGame::init(std::string windowTitle,int width,int height){
	this->width = width;
	this->height = height;
	char *argv [1];
	int argc=1;
	argv [0]=	"fake";
	glutInit( &argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH|GLUT_ALPHA);
	glutInitWindowSize(width,height);
	glutCreateWindow(windowTitle.c_str());
	glutDisplayFunc(BaseGame::display);
	glutIdleFunc(BaseGame::idle);
	glutReshapeFunc(BaseGame::onReshape);
	BaseGame::instance->lastTime = glutGet(GLUT_ELAPSED_TIME);
	BaseGame::instance->setupDone = false;
	glutMainLoop();


}

//glut static callback
void BaseGame::display(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0,0.0,0.0,1.0);
	
	if(!BaseGame::instance->setupDone){
		glewInit();
		BaseGame::instance->setup();
		BaseGame::instance->setupDone = true;
	}
	BaseGame::instance->draw();
}
//glut static callback
void BaseGame::idle(){
	
	int time = glutGet(GLUT_ELAPSED_TIME);

	BaseGame::instance->update((double)(glutGet(GLUT_ELAPSED_TIME) - BaseGame::instance->lastTime));
	BaseGame::instance->lastTime = time;
}
void BaseGame::onReshape(int width,int height){
	BaseGame::instance->reshape(width,height);
}


void BaseGame::postRedisplay(){

	glutPostRedisplay();
}

void BaseGame::swapBuffers(){
	glutSwapBuffers();
}
BaseGame::~BaseGame(void)
{
}

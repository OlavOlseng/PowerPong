#include "BulletDebugDraw.h"


BulletDebugDraw::BulletDebugDraw(LineModel * lineDrawer)
{
	this->lineDrawer = lineDrawer;
}


BulletDebugDraw::~BulletDebugDraw(void)
{
}


void BulletDebugDraw::drawLine (const btVector3 &from, const btVector3 &to, const btVector3 &color){
	
	lineDrawer->addLine(glm::vec3(from.getX(),from.getY(),from.getZ()),glm::vec3(to.getX(),to.getY(),to.getZ()),glm::vec3(color.getX(),color.getY(),color.getZ()));

}
void BulletDebugDraw::drawContactPoint (const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color)
{

throw "not implemented error";
}
void BulletDebugDraw::reportErrorWarning (const char *warningString)
{
	throw "not implemented error";
}
void BulletDebugDraw::draw3dText (const btVector3 &location, const char *textString)
{
	throw "not implemented error";
}
void BulletDebugDraw::setDebugMode (int debugMode)
{
	this->debugMode = debugMode;
}

void BulletDebugDraw::render(){
	lineDrawer->bufferLines();
	lineDrawer->clearLines();
	

}
int BulletDebugDraw::getDebugMode () const {
	
	return this->debugMode;

}
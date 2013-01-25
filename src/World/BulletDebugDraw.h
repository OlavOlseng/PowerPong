#ifndef BULLET_DEBUG_DRAW_H
#define BULLET_DEBUG_DRAW_H
#include "../Rendering/Models/LineModel.h"
#include "../bullet/btBulletCollisionCommon.h"
class BulletDebugDraw:public btIDebugDraw
{
public:

	BulletDebugDraw(LineModel * lineDrawer);
	~BulletDebugDraw(void);
	void drawLine (const btVector3 &from, const btVector3 &to, const btVector3 &color);
	void drawContactPoint (const btVector3 &PointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color);
	void reportErrorWarning (const char *warningString);
	void draw3dText (const btVector3 &location, const char *textString);
	void setDebugMode (int debugMode);
	int getDebugMode () const ;

	virtual void render();
private:
	int debugMode;
    LineModel * lineDrawer;
};

#endif
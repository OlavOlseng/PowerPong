#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H



#include <glm\glm.hpp>

class BoundingBox
{
public:
	BoundingBox(void);
	void setBounds(double xMin,double xMax,double yMin,double yMax,double zMin,double zMax);

	glm::vec3 getCenter();
	~BoundingBox(void);
private:
	glm::vec3 center;
	
};

#endif
#include "Light.h"


Light::Light(){
	

}

void PointLight::setRange(double range){
	this->constantAttenuation = 1.0;
	this->linearAttenutation = 4.5/range;
	this->quadraticAttenuation = 75.0/(range*range);
	
}
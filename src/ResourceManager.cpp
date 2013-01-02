#include "ResourceManager.h"


ResourceManager::ResourceManager(void)
{
}



void ResourceManager::setWorkingDirectory(std::string dir){
	this->workingDirectory = dir;

}
std::string ResourceManager::getWorkingDirectiory(){

	return this->workingDirectory;
}

ResourceManager::~ResourceManager(void)
{
}

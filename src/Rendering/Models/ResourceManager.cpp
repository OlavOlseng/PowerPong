#include "ResourceManager.h"


ResourceManager::ResourceManager(void)
{
}






Shader* ResourceManager::loadShader(std::string name){
	Shader * shader;
	
	
	if(shaders.find(name) ==shaders.end()){
		shader = new Shader(shaderDirectory+ name);
		shaders[name] = shader;
		
	}else{
		shader = shaders[name];
	}
	return shader;

}

GLuint ResourceManager::loadTexture(std::string name){
	GLuint texture;

	if(textures.find(name) == textures.end()){
		texture = ShaderUtil::loadTexture(modelDirectory+ name);
		textures[name] = texture;
	}else{
		texture = textures[name];
	}
	return texture;

}
void ResourceManager::setWorkingDirectory(std::string dir){
	this->workingDirectory = dir;

}
void ResourceManager::setShaderDirectory(std::string dir){
	this->shaderDirectory = dir;

}
void ResourceManager::setModelDirectory(std::string dir){
	this->modelDirectory = dir;
}
std::string ResourceManager::getWorkingDirectiory(){

	return this->workingDirectory;
}

std::string ResourceManager::getModelDirectory(){
	return this->modelDirectory;
}
std::string ResourceManager::getShaderDirectory(){
	return this->shaderDirectory;
}
ResourceManager::~ResourceManager(void)
{
}

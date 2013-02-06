#include "ResourceManager.h"


ResourceManager::ResourceManager(void)
{
}






Shader* ResourceManager::loadShader(std::string name,bool takeOwnership){
	Shader * shader;
	
	if(takeOwnership){
		shader = new Shader(shaderDirectory+ name);
		return shader;
	}
	
	if(shaders.find(name) ==shaders.end()){
		shader = new Shader(shaderDirectory+ name);
		int refrenceCount = 1;
		std::pair<Shader*,int> pair = std::make_pair(shader,refrenceCount);
		shaders[name] = pair;
		
	}else{
		std::pair<Shader*,int>  &pair = shaders[name];
		shader = pair.first;
		pair.second++;

	}
	return shader;

}

Texture *  ResourceManager::loadTexture(std::string name,bool takeOwnership){
	Texture *  texture;

	if(takeOwnership){
		texture = new Texture(ShaderUtil::loadTexture(modelDirectory+ name));
		return texture;
	}

	if(textures.find(name) == textures.end()){
		texture = new Texture(ShaderUtil::loadTexture(modelDirectory+ name));
		int refrenceCount = 1;
		std::pair<Texture *,int> pair = std::make_pair(texture,refrenceCount);
		textures[name] = pair;
	}else{
		std::pair<Texture *,int>  &pair = textures[name];
		texture = pair.first;
		pair.second++;
	}
	return texture;

}

const aiScene * ResourceManager::loadModel(std::string name,int postProcess){
	const aiScene * scene;

	Assimp::Importer * imp = new Assimp::Importer();
	if(models.find(name) == models.end()){
		scene = imp->ReadFile(modelDirectory + name,postProcess);
		int refrenceCount = 1;
		std::pair<std::pair<Assimp::Importer*,const aiScene*>,int> pair = std::make_pair(std::make_pair(imp,scene),refrenceCount);
		models[name]= pair;
	}else{
		std::pair<std::pair<Assimp::Importer*,const aiScene*>,int> &pair = models[name];
		scene = pair.first.second;
		pair.second++;
	}
	return scene;

}

void ResourceManager::freeTexture(std::string name){

	std::pair<Texture *,int> &pair = textures[name];

	pair.second--;
	if(pair.second == 0){
		delete pair.first;
		textures.erase(name);
	}




}
void ResourceManager::freeModel(std::string name){

	std::pair<std::pair<Assimp::Importer*,const aiScene*>,int> &pair = models[name];

	pair.second--;
	if(pair.second == 0){
		pair.first.first->FreeScene();
		delete pair.first.first;
		models.erase(name);
	}



}
void ResourceManager::freeShader(std::string name){

	std::pair<Shader*,int> &pair = shaders[name];

	pair.second--;
	if(pair.second == 0){
		delete pair.first;
		shaders.erase(name);

	}

	

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


template<typename T>
LargeVolume<T>::LargeVolume(unsigned int width,unsigned int height ,unsigned int depth,unsigned int subWidth,unsigned int subHeight,unsigned int subDepth)
{
	
	
	this->numX = (width/subWidth);
	this->numY = (height/subHeight);
	this->numZ = (depth/subDepth);

	this->subWidth = subWidth;
	this->subHeight = subHeight;
	this->subDepth = subDepth;

	this->width = width;
	this->height = height;
	this->depth = depth;
	subVolumes = (Volume**)(new T*[numX*numY*numZ]);

	for(unsigned int x = 0;x < numX;x++){
		for (unsigned int y = 0; y < numY;y++){
			for (unsigned int z = 0;z < numZ;z++){
				subVolumes[getIndex(x,y,z)] = new T(subWidth,subHeight,subDepth);

			}
		}
	}


}

template<typename T>
void LargeVolume<T>::set(int x,int y,int z,BlockType type){

	this->getSubVolume(x,y,z)->set(x % subWidth,y % subHeight,z % subDepth,type);

}

template<typename T>
inline unsigned int LargeVolume<T>::getIndex(int x,int y,int z){

	return x + y*numY + z*numZ*numZ;

}

template<typename T>
inline Volume * LargeVolume<T>::getSubVolume(int x,int y,int z){
	

	return subVolumes[this->getIndex(x/subWidth,y/subDepth,z/subDepth)];

}
template<typename T>
BlockType LargeVolume<T>::get(int x,int y,int z){

	return this->getSubVolume(x,y,z)->get(x % subWidth,y % subHeight, z % subDepth);

}

template<typename T>
bool LargeVolume<T>::isInvisible(){
	
	return this->invisible;

}

template<typename T>
bool LargeVolume<T>::isEmpty(){

	return false;

}

template<typename T>
void LargeVolume<T>::setInvisible(bool invisible){
	this->invisible = invisible;

}

template<typename T>
LargeVolume<T>::~LargeVolume(void)
{
	for (unsigned int i = 0; i<numX*numY*numZ;i++){
		delete subVolumes[i];

	}
	delete subVolumes;
}

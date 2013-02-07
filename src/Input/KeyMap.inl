
template <typename idType,typename valueType>
KeyMap<idType,valueType>::KeyMap(void)
{
}

template <typename idType,typename valueType>
void KeyMap<idType,valueType>::setKey(char character, idType identifier,valueType value){

	this->charactermap[character] = std::make_pair(identifier,value);


}
template <typename idType,typename valueType>
bool KeyMap<idType,valueType>::hasKey(char character){

	return charactermap.find(character) != charactermap.end();
	
}
template <typename idType,typename valueType>
std::pair<idType,valueType> KeyMap<idType,valueType>::getKey(char character){
	return charactermap[character];

}


template <typename idType,typename valueType>
std::pair<typename m_iter<idType,valueType>::iterator_t,typename m_iter<idType,valueType>::iterator_t> KeyMap<idType,valueType>::getKeys(){

	return std::make_pair(charactermap.begin(),charactermap.end());
}


template <typename idType,typename valueType>
typename std::hash_map<char,std::pair<idType,valueType>>::iterator KeyMap<idType,valueType>::begin(){

	return charactermap.begin();

}

template <typename idType,typename valueType>
typename std::hash_map<char,std::pair<idType,valueType>>::iterator KeyMap<idType,valueType>::end(){

	return charactermap.end();

}


template <typename idType,typename valueType>
KeyMap<idType,valueType>::~KeyMap(void)
{
}

#ifndef KEY_MAP_H
#define KEY_MAP_H

#include <hash_map>

template <typename T1,typename T2>
struct m_iter{
	typedef typename std::hash_map<char,std::pair<T1,T2>>::iterator iterator_t;
};




template <typename idType,typename valueType>
class KeyMap
{
public:
	
	
	KeyMap(void);
	void setKey(char character, idType identifier,valueType value);
	bool hasKey(char character);
	std::pair<idType,valueType> getKey(char character);
	//returns a begin() and end() iterator
	std::pair<typename m_iter<idType,valueType>::iterator_t,typename m_iter<idType,valueType>::iterator_t> getKeys();


	typename std::hash_map<char,std::pair<idType,valueType>>::iterator begin();
	typename std::hash_map<char,std::pair<idType,valueType>>::iterator end();

	~KeyMap(void);

private:
	std::hash_map<char,std::pair<idType,valueType>> charactermap;
};



#include "KeyMap.inl"


#endif
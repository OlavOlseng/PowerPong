#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include "Entity.h"

class Block: public Entity
{
public:
	Block(float x, float y, float z);
	Block(float width, float height, float depth, float x, float y, float z);
	~Block(void);
};


#endif
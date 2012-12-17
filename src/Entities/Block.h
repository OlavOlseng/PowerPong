#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include "Entity.h"

class Block: public Entity
{
public:
	Block(int width, float x, float y, float z);
	~Block(void);
};

#endif
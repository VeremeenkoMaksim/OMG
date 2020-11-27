#pragma once
#include "Enemy.h"

class Goblin : public Enemy
{
private: 

public:
	Goblin();
	virtual bool init() override;

};
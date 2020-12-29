#pragma once
#include "Enemy.h"

class Ogre : public Enemy
{
private:
	static void loadAnimations(Ogre* enemy);
public:
	Ogre();
	virtual bool init() override;

};
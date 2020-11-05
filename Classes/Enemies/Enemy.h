#include "cocos2d.h"

class Enemy
{
public:
	virtual bool init();

	void update(float dt);
};
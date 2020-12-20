#pragma once
#include "Tower.h"

class BasicTower : public Tower
{
private:

	virtual void Shoot(float damage);
public:
	virtual bool init() override;
	virtual void update(float dt);
	BasicTower(int tileX, int tileY);
};
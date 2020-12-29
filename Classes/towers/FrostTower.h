#pragma once
#include "Tower.h"

class FrostTower : public Tower
{
private:
	nlohmann::json data;
	virtual void Shoot(float damage);
public:
	virtual bool init() override;
	virtual void update(float dt);
	FrostTower(int tileX, int tileY);
};
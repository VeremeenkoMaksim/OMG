#pragma once
#include "Tower.h"
#include "../Classes/json/json.hpp"
class BasicTower : public Tower
{
private:
	nlohmann::json data;

public:
	virtual bool init() override;
	virtual void update(float dt);
	BasicTower();
};
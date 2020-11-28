#pragma once
#include "cocos2d.h" 
#include "../Classes/enemies/Enemy.h"
class Tower : public cocos2d::Node
{
protected:
	float range = 10;
	float attackSpeed = 10;
	float damage = 10;
	float currCooldown;
	float cooldown;
	cocos2d::Node* targetEnemy;
	cocos2d::Sprite* sprite;

public:
	virtual bool init();
	virtual bool CanShoot();
	virtual void SearchTarget();
	//virtual void Shoot();
	virtual void update(float dt);
};
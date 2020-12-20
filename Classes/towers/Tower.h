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
	Enemy* targetEnemy = nullptr;
	cocos2d::Sprite* sprite;
	cocos2d::Sprite* projectileSprite;
	virtual void Shoot(float damage);
public:
	virtual bool init();
	virtual bool CanShoot();
	virtual bool SearchTarget();
	virtual void update(float dt);
};
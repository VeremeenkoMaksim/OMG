#pragma once
#include "cocos2d.h" 
#include "../Classes/enemies/Enemy.h"
#include "../Classes/Json/JsonInstance.h"
class Tower : public cocos2d::Node
{
protected:
	nlohmann::json data;
	float range;
	float attackSpeed;
	float damage;
	float currCooldown;
	float cooldown;
	Enemy* targetEnemy = nullptr;
	cocos2d::Sprite* sprite;
	cocos2d::Sprite* projectileSprite;
	virtual void Shoot(float damage);
	cocos2d::Vec2 position;

public:
	Tower(int tileX, int tileY);
	virtual bool init();
	virtual bool CanShoot();
	virtual bool SearchTarget();
	virtual void update(float dt);
	int cost;
};
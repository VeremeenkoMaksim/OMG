#pragma once
#include "cocos2d.h" 
#include "../Classes/enemies/Enemy.h"
#include "../Classes/Json/JsonInstance.h"
class Projectile : public cocos2d::Node
{
protected:
	nlohmann::json data;
	cocos2d::Sprite * sprite;
	float speed;
	float damage;
	Enemy * target;
	virtual bool init();
	virtual void update(float dt);
	bool MoveToTarget(Enemy * target, float dt);
	cocos2d::Vec2 FindDirection(cocos2d::Vec2 currentPos, cocos2d::Vec2 targetPos);
public:
	Projectile(Enemy * target, float speed, float damage);
};
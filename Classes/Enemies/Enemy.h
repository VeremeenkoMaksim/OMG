#pragma once
#include "cocos2d.h"
#include "../Classes/Json/JsonInstance.h"

class Enemy : public cocos2d::Node
{
protected: 
	float health;
	float speed;
	float damage;
	cocos2d::Sprite * sprite;
	int wayNum = 0;
	bool Move(float dt);

	cocos2d::Vec2 nextPosOnTheWay;
	cocos2d::Vec2 distanceToPosOnTheWay;
	cocos2d::Vec2 direction;
	cocos2d::Vec2 FindDirection(cocos2d::Vec2 distanceToPosOnTheWay);
	nlohmann::json data;
	
	void Dead();

	cocos2d::Label *label;
public:
	virtual bool init();
	virtual void DamageDeal();
	virtual void ReceiveDamage(float damage);
	virtual void update(float dt);
	bool isDead() {
		return health <= 0;
	};
};
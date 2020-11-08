#include "cocos2d.h" 
class Enemy : public cocos2d::Node
{
protected: 
	float health = 100;
	float speed = 10;
	float damage = 10;
	cocos2d::Sprite * sprite;
	int wayNum = 0;
	void Move(float dt);
	cocos2d::Vec2 nextPosOnTheWay;
	cocos2d::Vec2 distanceToPosOnTheWay;
	cocos2d::Vec2 direction;
	cocos2d::Vec2 FindDirection(cocos2d::Vec2 distanceToPosOnTheWay);
public:
	virtual bool init();
	virtual void ReceiveDamage(float damage);
	virtual void update(float dt);
};
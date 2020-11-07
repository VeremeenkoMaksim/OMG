#include "cocos2d.h" 
class Enemy : public cocos2d::Node
{
protected: 
	float health = 100;
	float speed = 10;
	float damage = 10;
	cocos2d::Sprite * sprite;
	int wayNum = 1;

public:
	virtual bool init();
	virtual void ReceiveDamage(float damage);
	virtual void update(float dt);
};
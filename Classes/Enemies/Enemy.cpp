#include "Enemy.h"
#include "Field.h"
#include <cmath>

bool Enemy::init() {
	cocos2d::Vec2 position = Field::GetInstance()->GetTheWay()[wayNum-1]->getPosition();
	this->setPosition(position);
	this->scheduleUpdate();
	return true;
}

void Enemy::ReceiveDamage(float damage) {
	health -= damage;
}

void Enemy::update(float dt) {
	cocos2d::Vec2 nextPosOnTheWay = Field::GetInstance()->GetTheWay()[wayNum]->getPosition();
	cocos2d::Vec2 dif = nextPosOnTheWay - this->getPosition();
	cocos2d::Vec2 dir = cocos2d::Vec2(dif.x > 0 ? 1 : 0, dif.y != 0 ? 1 : 0);
	if (dif.x < 0)
		dir.x = -1;
	if (dif.x > 0)
		dir.x = 1;
	if (dif.y < 0)
		dir.y = -1;
	if (dif.y > 0)
		dir.y = 1;
	if (abs(dif.x) > 1 || abs(dif.y) > 1) {
		this->setPosition(this->getPosition().x + speed * dt * dir.x, this->getPosition().y + speed * dt * dir.y);
	}
	else if (wayNum < 5) {
		this->setPosition(nextPosOnTheWay);
		wayNum++;
	}
}

#pragma once
#include "Enemy.h"
#include "Field.h"
#include <cmath>
#include "towers/mainHouse.h"

#define WIDTH_AND_HEIGTH_OF_TILE 76.f;
bool Enemy::init() {
	
	float f = WIDTH_AND_HEIGTH_OF_TILE;
	nextPosOnTheWay = Field::GetInstance()->GetTheWay()[wayNum]->getPosition();
	this->setPosition(nextPosOnTheWay);
	distanceToPosOnTheWay = nextPosOnTheWay - this->getPosition();
	direction = FindDirection(distanceToPosOnTheWay);
	this->scheduleUpdate();
	return true;
}

void Enemy::ReceiveDamage(float damage) {
	health -= damage;
}

void Enemy::update(float dt) {
	if (!Move(dt))
		DamageDeal();
}

bool Enemy::Move(float dt) {
	if (wayNum < Field::GetInstance()->GetTheWay().size()-1) {
		distanceToPosOnTheWay = nextPosOnTheWay - this->getPosition();
		if (distanceToPosOnTheWay.x * direction.x > 10  || distanceToPosOnTheWay.y  * direction.y > 10) {
			this->setPosition(this->getPosition().x + speed * dt * direction.x, this->getPosition().y + speed * dt * direction.y);
		}
		else if((wayNum < Field::GetInstance()->GetTheWay().size() - 1)) {
			this->setPosition(nextPosOnTheWay);
			wayNum++;
			nextPosOnTheWay = Field::GetInstance()->GetTheWay()[wayNum]->getPosition();
			distanceToPosOnTheWay = nextPosOnTheWay - this->getPosition();
			direction = FindDirection(distanceToPosOnTheWay);
		} else this->setPosition(nextPosOnTheWay);
		return true;
	}
	else
		return false;
}

void Enemy::DamageDeal() {
	MainHouse::GetInstance()->ReceiveDamage(damage);
}

cocos2d::Vec2 Enemy::FindDirection(cocos2d::Vec2 distanceToPosOnTheWay) {
	cocos2d::Vec2 dir;
	if (distanceToPosOnTheWay.x < 0)
		dir.x = -1;
	else if (distanceToPosOnTheWay.x > 0)
		dir.x = 1;
	if (distanceToPosOnTheWay.y < 0)
		dir.y = -1;
	else if (distanceToPosOnTheWay.y > 0)
		dir.y = 1;
	return dir;
}




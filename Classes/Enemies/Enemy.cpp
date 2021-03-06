#pragma once
#include "Enemy.h"
#include "Field.h"
#include <cmath>
#include "towers/mainHouse.h"
#include "../Classes/scenes/Level_1.h"
USING_NS_CC;

bool Enemy::init() {
	nextPosOnTheWay = Field::GetInstance()->GetNodesOfTheWay()[wayNum]->getPosition();
	this->setPosition(nextPosOnTheWay);
	distanceToPosOnTheWay = nextPosOnTheWay - this->getPosition();
	direction = FindDirection(distanceToPosOnTheWay);

	this->scheduleUpdate();
	return true;
}

void Enemy::ReceiveDamage(float damage) {
	health -= damage;
	label->setString(std::to_string(health));
	if (health <= 0 && !dead) {
		dead = true;
		Level_1::GetInstance()->economy->AddGold(cost);
	}
}

void Enemy::update(float dt) {
	if (!Move(dt)) {
		DamageDeal();
		cocos2d::Director::getInstance()->getRunningScene()->getChildByName("Enemies")->removeChild(this, false);
		dead = true;
	}
}

bool Enemy::Move(float dt) {
	if (wayNum < Field::GetInstance()->GetNodesOfTheWay().size()) {
		distanceToPosOnTheWay = nextPosOnTheWay - this->getPosition();
		if (distanceToPosOnTheWay.x * direction.x > speed * dt || distanceToPosOnTheWay.y * direction.y > speed * dt) {
			this->setPosition(this->getPosition().x + speed * dt * direction.x, this->getPosition().y + speed * dt * direction.y);
		}
		else {
			this->setPosition(nextPosOnTheWay);
			wayNum++;
			if ((wayNum < Field::GetInstance()->GetNodesOfTheWay().size())) {
				nextPosOnTheWay = Field::GetInstance()->GetNodesOfTheWay()[wayNum]->getPosition();
				distanceToPosOnTheWay = nextPosOnTheWay - this->getPosition();
				direction = FindDirection(distanceToPosOnTheWay);
			}
		}
		return true;
	}
	else {
		return false;
	}
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
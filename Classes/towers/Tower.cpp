#pragma once
#include "Tower.h"
#include "Field.h"


bool Tower::init() {
	cocos2d::Vec2 position = Field::GetInstance()->tiles[1][1]->getPosition();
	this->setPosition(position);
	this->scheduleUpdate();
	return true;


}

void Tower::update(float dt) {
	if (CanShoot())
		SearchTarget();
	if (currCooldown > 0)
		currCooldown -= dt;
}

bool Tower::CanShoot() {	
	if (currCooldown <= 0)
		return true;
	return  false;
}

void Tower::SearchTarget() {


	if (targetEnemy == NULL) {
		cocos2d::Vec2 nearestEnemy = NULL;
		float minDistance = INFINITE;
		auto enemies = cocos2d::Director::getInstance()->getRunningScene()->getChildren();
		for (int i = 0; i < enemies.size(); i++) {
			auto distance = this->getPosition().distance(enemies.at(i)->getPosition());
			if (distance < minDistance && distance <= range) {
				//targetEnemy = enemies.at(i);
				minDistance = distance;
			}
		}
	}
}
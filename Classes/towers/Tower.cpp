#pragma once
#include "Tower.h"
#include "Field.h"
#include "../Classes/enemies/Enemy.h"
#include "../Classes/scenes/Level_1.h"
#include <vector>

bool Tower::init() {
	cocos2d::Vec2 position = Field::GetInstance()->tiles[5][5]->getPosition();
	this->setPosition(position);
	currCooldown = 0;
	this->scheduleUpdate();
	return true;
}

void Tower::update(float dt) {
	if (CanShoot()) {
		if (SearchTarget()) {
			Shoot(damage);
		}
	}
	if (currCooldown > 0)
		currCooldown -= dt;
}

bool Tower::CanShoot() {	
	if (currCooldown <= 0){
		return true;
	}
	return  false;
}

bool Tower::SearchTarget() {
	if (targetEnemy) {
		auto distance = this->getPosition().distance(targetEnemy->getPosition());
		if (distance > range) {
			targetEnemy = nullptr;
		}
	}
	if (!targetEnemy) {
		float minDistance = INFINITE;
		auto nodes = cocos2d::Director::getInstance()->getRunningScene()->getChildren();
		std::vector<Enemy*> enemies = Level_1::GetInstance()->GetEnemies();
		for (int i = 0; i < enemies.size(); i++) {
			auto distance = this->getPosition().distance(enemies.at(i)->getPosition());
			if (distance < minDistance && distance <= range) {
				targetEnemy = enemies.at(i);
				targetEnemy->addChild(cocos2d::DrawNode::create());
				minDistance = distance;
			}
		}
	}

	if (targetEnemy)
		return true;
	else return false;
}

void Tower::Shoot(float damage) {
	currCooldown = cooldown;
	targetEnemy->ReceiveDamage(damage);
}
#pragma once
#include "Tower.h"
#include "Field.h"
#include "../Classes/enemies/Enemy.h"
#include "../Classes/scenes/Level_1.h"
#include "../Classes/projectiles/BasicProjectile.h"
#include <vector>


Tower::Tower(int tileX, int tileY) {
	position = Field::GetInstance()->tiles[tileY][tileX]->getPosition();
}
bool Tower::init() {
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
		auto enemiesNodes = cocos2d::Director::getInstance()->getRunningScene()->getChildByName("Enemies")->getChildren();
		for (int i = 0; i < enemiesNodes.size(); i++) {
			auto distance = this->getPosition().distance(enemiesNodes.at(i)->getPosition());
			if (distance < minDistance && distance <= range) {
				targetEnemy = dynamic_cast<Enemy*>(enemiesNodes.at(i));
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
	auto projectile = new BasicProjectile(targetEnemy, attackSpeed, damage);
	projectile->setPosition(this->getPosition());
	this->getParent()->addChild(projectile, 10);


	if (targetEnemy->isDead()) 
		cocos2d::Director::getInstance()->getRunningScene()->getChildByName("Enemies")->removeChild(targetEnemy,false); {
		targetEnemy = nullptr;
	}
}
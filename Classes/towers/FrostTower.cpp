#pragma once
#include "FrostTower.h"
#include "Field.h"
#include <vector>


FrostTower::FrostTower(int tileX, int tileY) : Tower(tileX, tileY) {
	data = JsonInstance::GetInstance()->GetData("towers")["FrostTower"];
	init();
}
bool FrostTower::init() {
	Tower::init();
	sprite = cocos2d::Sprite::create(data["Image"]);
	sprite->setScale(data["Scale"]);
	this->addChild(sprite);
	range = data["Stats"]["Range"];
	attackSpeed = data["Stats"]["AttackSpeed"];
	damage = data["Stats"]["Damage"];
	cooldown = data["Stats"]["Cooldown"];
	return true;
}

void FrostTower::update(float dt)
{
	Tower::update(dt);
}

void FrostTower::Shoot(float damage) {
	Tower::Shoot(damage);
}
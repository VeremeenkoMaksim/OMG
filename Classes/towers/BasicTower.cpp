#pragma once
#include "BasicTower.h"
#include "Field.h"
#include <vector>


BasicTower::BasicTower(int tileX, int tileY) : Tower(tileX, tileY) {
	data = JsonInstance::GetInstance()->GetData("towers")["BasicTower"];
	init();
}
bool BasicTower::init() {
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

void BasicTower::update(float dt)
{
	Tower::update(dt);
}

void BasicTower::Shoot(float damage) {

	Tower::Shoot(damage);
}
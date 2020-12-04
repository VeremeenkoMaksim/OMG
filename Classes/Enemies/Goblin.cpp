#pragma once
#include "Goblin.h"

Goblin::Goblin() {
	data = JsonInstance::GetInstance()->GetData("enemies")["Goblin"];
	init();
}
bool Goblin::init() {
	Enemy::init();
	sprite = cocos2d::Sprite::create(data["Image"]);
	this->addChild(sprite);
	this->setScale(data["Scale"]);
	health = data["Stats"]["Health"];
	speed = data["Stats"]["Speed"];
	damage = data["Stats"]["Damage"];
	return true;
}

#pragma once
#include "Goblin.h"
USING_NS_CC;

Goblin::Goblin() {
	data = JsonInstance::GetInstance()->GetData("enemies")["Goblin"];
	init();
}
bool Goblin::init() {
	Enemy::init();
	sprite = cocos2d::Sprite::create(data["Image"]);
	sprite->setScale(data["Scale"]);
	this->addChild(sprite);
	health = data["Stats"]["Health"];
	speed = data["Stats"]["Speed"];
	damage = data["Stats"]["Damage"];
	cost = data["Cost"];

	label = cocos2d::Label::create();
	label->setString(std::to_string(health));
	label->setPosition(0, 45);
	this->addChild(label, 10);
	return true;
}
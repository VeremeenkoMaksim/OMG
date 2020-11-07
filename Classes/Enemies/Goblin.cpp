#include "Goblin.h"
#include "Field.h"
#include <vector>

Goblin::Goblin() {
	init();
}
bool Goblin::init() {
	Enemy::init();
	sprite = cocos2d::Sprite::create("enemies/goblin/idle/0.png");
	sprite->setScale(0.1);
	this->addChild(sprite);
	health = 100;
	speed = 140;
	damage = 5;
	return true;
}

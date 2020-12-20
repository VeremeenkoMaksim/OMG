#pragma once
#include "BasicProjectile.h"

BasicProjectile::BasicProjectile(Enemy * target, float speed, float damage)
	: Projectile(target,speed, damage) {
	data = JsonInstance::GetInstance()->GetData("projectiles")["BasicProjectile"];
	init();
}

bool BasicProjectile::init() {
	Projectile::init();
	sprite = cocos2d::Sprite::create(std::string(data["Image"]));
	sprite->setScale(data["Scale"]);
	this->addChild(sprite);
	return true;
}
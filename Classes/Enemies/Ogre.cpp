#pragma once
#include "Ogre.h"
USING_NS_CC;

Ogre::Ogre() {
	data = JsonInstance::GetInstance()->GetData("enemies")["Ogre"];
	init();
}
bool Ogre::init() {
	Enemy::init();
	sprite = cocos2d::Sprite::create(data["Image"]);
	sprite->setScale(data["Scale"]);
	this->addChild(sprite);
	health = data["Stats"]["Health"];
	speed = data["Stats"]["Speed"];
	damage = data["Stats"]["Damage"];

	/*animationPath = data["Animation"]["SpriteSheet"];
	numberOfFrames = data["Animation"]["NumOfFrames"];
	animationSpeed = data["Animation"]["AnimationSpeed"];*/

	label = cocos2d::Label::create();
	label->setString(std::to_string(health));
	label->setPosition(0, 45);
	this->addChild(label, 10);
	return true;
}


#pragma once
#include "MainHouse.h"
#include "Field.h"
MainHouse* MainHouse::singleton = 0;

MainHouse* MainHouse::GetInstance() {
	if (!singleton) {
		singleton = new MainHouse();
	}
	return singleton;
}
MainHouse::MainHouse() {
	data = JsonInstance::GetInstance()->GetData("towers")["MainHouse"];
	label = cocos2d::Label::create();
	label->setString(std::to_string(health));
	label->setPosition(0, -45);
	this->addChild(label,10);
	init();
}

bool MainHouse::init() {
	sprite = cocos2d::Sprite::create(data["Image"]);
	sprite->setScale(data["Scale"]);
	cocos2d::Vec2 position = Field::GetInstance()->GetTheWay()[Field::GetInstance()->GetTheWay().size()-1]->getPosition();
	this->setPosition(position.x, position.y);
	this->addChild(sprite, 10);
	return true;
}

void MainHouse::ReceiveDamage(float damage) {
		health -= damage;
		label->setString(std::to_string(health));
}
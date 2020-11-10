#pragma once
#include "Level_1.h"
#include "Field.h"
#include "enemies/Goblin.h"

USING_NS_CC;

Scene* Level_1::createScene()
{
    return Level_1::create();
}

bool Level_1::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto resolution = Label::create();
    resolution->setString(std::to_string(visibleSize.height) + " " + std::to_string(visibleSize.width));
    resolution->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - resolution->getContentSize().height + 10));
    this->addChild(resolution);

	this->addChild(Field::GetInstance()->CreateField(13,10), -1);
	Enemy * goblin = new Goblin();
	this->addChild(goblin, 10);
    this->scheduleUpdate();
    return true;
}

void Level_1::update(float dt) {
	//imgui();
}

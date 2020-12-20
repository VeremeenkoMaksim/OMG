#pragma once
#include "Level_1.h"
#include "Field.h"
#include "towers/MainHouse.h"
#include "AudioEngine.h"
#include "LevelFinishScene.h"

USING_NS_CC;
Level_1* Level_1::singleton = 0;
Scene* Level_1::createScene()
{
    return Level_1::create();
}

Level_1 * Level_1::GetInstance() {
	return singleton;
}

bool Level_1::init()
{
    if (!Scene::init())
    {
        return false;
    }
	singleton = this;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto resolution = Label::create();
    resolution->setString(std::to_string(visibleSize.height) + " " + std::to_string(visibleSize.width));
    resolution->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height - resolution->getContentSize().height + 10));
    
    this->addChild(resolution);

	this->addChild(Field::GetInstance()->CreateField(13,10), -1);

	auto lab = cocos2d::Label::create();
	lab->setString("1000");
	this->addChild(lab);

    Enemy* goblin = new Goblin();
	enemies.push_back(goblin);
	this->addChild(goblin, 10);

    Tower * basicTower = new BasicTower();//----------adding basictower
    this->addChild(basicTower, 10);
    
  
    this->addChild(MainHouse::GetInstance(), 10);

    this->scheduleUpdate();
    
    return true;
}

void Level_1::update(float dt) {

 
}

std::vector<Enemy*> Level_1::GetEnemies() {
	return enemies;
}

void Level_1::GameOver(bool win) {
    Scene* scene = LevelFinish::createScene();
    TransitionFade* transition = TransitionFade::create(2, scene);
    dynamic_cast<LevelFinish *>(scene)->win = win;
    
    //AudioEngine::stopAll();
    //AudioEngine::end();
    Director::getInstance()->replaceScene(scene);
}
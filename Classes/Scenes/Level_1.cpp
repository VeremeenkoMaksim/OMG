#pragma once
#include "Level_1.h"
#include "Field.h"
#include "towers/MainHouse.h"
#include "AudioEngine.h"
#include "LevelFinishScene.h"
#include "enemies/Goblin.h"
#include "enemies/Ogre.h"
#include "towers/BasicTower.h"
#include "towers/FrostTower.h"

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
	
	enemies = cocos2d::Node::create();
	enemies->setName("Enemies");
	this->addChild(enemies);
    Tower * basicTower = new BasicTower(6,4);
    this->addChild(basicTower, 10);

	Tower * basicTower1 = new BasicTower(8, 4);
	this->addChild(basicTower1, 10);
    
	Tower * basicTower2 = new BasicTower(8, 5);
	this->addChild(basicTower2, 10);
	
	Tower * basicTower3 = new BasicTower(6, 5);
	this->addChild(basicTower3, 10);

    Tower* frostTower = new FrostTower(1,1);
    this->addChild(frostTower, 10);

    this->addChild(MainHouse::GetInstance(), 10);

    this->scheduleUpdate();
    
	auto buyTowerBtn = MenuItemImage::create("UI/buttons/images/buyTowerBtn.png", "UI/buttons/images/buyTowerBtnSelected.png", CC_CALLBACK_1(Level_1::BuyTower, this));
	buyTowerBtn->setPosition(970, 30);
	buyTowerBtn->setScale(0.3);

	auto menu = Menu::create(buyTowerBtn, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	auto touchListener = EventListenerTouchOneByOne::create();

    return true;
}
void Level_1::BuyTower(Ref * sender) {
	
}
void Level_1::update(float dt) {

    if (cooldown <= 0) {
        if (waveCount > 0) {
            Enemy* goblin = new Goblin();
            enemies->addChild(goblin, 10);
            Enemy* ogre = new Ogre();
            enemies->addChild(ogre, 10);
            cooldown = 1;
            waveCount--;
        }
    }
    else {
        cooldown -= dt;
    }
}

void Level_1::GameOver(bool lose) {
    Scene* scene = LevelFinish::createScene();
    TransitionFade* transition = TransitionFade::create(2, scene);
    dynamic_cast<LevelFinish *>(scene)->lose = lose;
    
    //AudioEngine::stopAll();
    //AudioEngine::end();
    Director::getInstance()->replaceScene(scene);
}
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

	resolution = Director::getInstance()->getOpenGLView()->getFrameSize();
    
	this->addChild(Field::GetInstance()->CreateField(13,10), -1); //hardcode layer
	
	enemies = cocos2d::Node::create();
	enemies->setName("Enemies");
	this->addChild(enemies);

    this->addChild(MainHouse::GetInstance(), 10);

    this->scheduleUpdate();
    
	auto buyTowerBtn = MenuItemImage::create("UI/buttons/images/buyTowerBtn.png", "UI/buttons/images/buyTowerBtnSelected.png", CC_CALLBACK_1(Level_1::BuyTower, this));
	buyTowerBtn->setLocalZOrder(1000); //hardcode layer
	buyTowerBtn->setPosition(970, 30); 
	buyTowerBtn->setScale(0.3);

	auto menu = Menu::create(buyTowerBtn, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(Level_1::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	storeUI = StoreUI::Create();
	this->addChild(storeUI);
	
    return true;
}

bool Level_1::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event) {
	if (storeUI->building) {
		Field::GetInstance()->RemoveGrid();
		storeUI->building = false;
		auto field = Field::GetInstance();
		int tileX = touch->getLocation().x / (resolution.width/ field->GetTilesSize().width);
		int tileY = touch->getLocation().y / (resolution.height / field->GetTilesSize().height);
		if (field->tiles[tileY][tileX]->empty) {
			if (storeUI->buildingTower == "BasicTower") {
				auto tower = new BasicTower(tileX, tileY);
				field->tiles[tileY][tileX]->SetTower(tower);
				this->addChild(tower);
			}
		}
	}
	return true;
}

void Level_1::BuyTower(Ref * sender) {
	if (!storeUI->building) {
		storeUI->building = false;
	}

	if (!storeUI->opened) {
		storeUI->OpenStore();
	}
	else
	{
		storeUI->CloseStore();
	}
}
void Level_1::update(float dt) {

    if (cooldown <= 0) {
        if (waveCount > 0) {
            Enemy* goblin = new Goblin();
            enemies->addChild(goblin, 10);
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
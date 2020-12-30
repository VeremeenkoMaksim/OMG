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

	resolution = Director::getInstance()->getOpenGLView()->getFrameSize();

	this->addChild(Field::GetInstance()->CreateField(13, 10), -1); //hardcode layer

	enemies = cocos2d::Node::create();
	enemies->setName("Enemies");
	this->addChild(enemies);

	this->addChild(MainHouse::GetInstance(), 10);

	auto buyTowerBtn = MenuItemImage::create("UI/images/buttons/buyTowerBtn.png", "UI/images/buttons/buyTowerBtnSelected.png", CC_CALLBACK_1(Level_1::BuyTower, this));
	buyTowerBtn->setLocalZOrder(1000); //hardcode layer
	buyTowerBtn->setPosition(970, 30);
	buyTowerBtn->setScale(0.3);

	

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(Level_1::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	storeUI = StoreUI::Create();
	this->addChild(storeUI);

	economy = new Economy(100);
	this->addChild(economy->CreateUIGold());

	data = JsonInstance::GetInstance()->GetData("levels")["Level_1"];

	startWaveBtn = MenuItemImage::create("UI/images/buttons/PlayWave.png", "UI/images/buttons/PlayWaveSelected.png", CC_CALLBACK_1(Level_1::StartWave, this));
	startWaveBtn->setLocalZOrder(1000); //hardcode layer
	startWaveBtn->setPosition(850, 30);

	auto menu = Menu::create(buyTowerBtn, startWaveBtn,  NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);

	this->scheduleUpdate();
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
				if (economy->GetGolgAmount() >= tower->cost) {
					field->tiles[tileY][tileX]->SetTower(tower);
					this->addChild(tower);
					economy->DeductGold(tower->cost);
				}
			}
		}
	}
	return true;
}

void Level_1::BuyTower(Ref * sender) {
	if (waveStarted)
		return;
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
void Level_1::StartWave(Ref * sender) {
	waveStarted = true;
}
void Level_1::update(float dt) {
	if (!waveStarted)
		return;

	if(data["Waves"].contains("Wave_" + std::to_string(waveCount))) {
		if(data["Waves"]["Wave_" + std::to_string(waveCount)].contains(std::to_string(wavePartCount))) {
			if (data["Waves"]["Wave_" + std::to_string(waveCount)][std::to_string(wavePartCount)]["Type"] == "Goblin") {
				if (enemiesCount == 0) {
					enemiesCount = data["Waves"]["Wave_" + std::to_string(waveCount)][std::to_string(wavePartCount)]["Count"];
				} 
				if (enemiesCount > 0) {
					if (enemiesCooldown <= 0) {
						enemiesCount--;
						auto goblin = new Goblin();
						enemies->addChild(goblin, 10);
						enemiesCooldown = 0.2;
						if (enemiesCount == 0)
							wavePartCount++;
					}
					else {
						enemiesCooldown -= dt;
					}
				}
			}
			else if (data["Waves"]["Wave_" + std::to_string(waveCount)][std::to_string(wavePartCount)]["Type"] == "Ogre") {
				if (enemiesCount == 0) {
					enemiesCount = data["Waves"]["Wave_" + std::to_string(waveCount)][std::to_string(wavePartCount)]["Count"];
				}
				if (enemiesCount > 0) {
					if (enemiesCooldown <= 0) {
						enemiesCount--;
						auto goblin = new Ogre();
						enemies->addChild(goblin, 10);
						enemiesCooldown = 1;
						if (enemiesCount == 0)
							wavePartCount++;
					}
					else {
						enemiesCooldown -= dt;
					}
				}
			}
		}
		else {
			wavePartCount = 1;
			waveCount++;
			if (data["Waves"].contains("Wave_" + std::to_string(waveCount))) {
				waveStarted = false;
			}
		}
	}
	else {
		//GameOver(false);
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
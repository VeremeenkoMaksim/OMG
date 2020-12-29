#pragma once
#include "cocos2d.h"
#include "enemies/Goblin.h"
#include "towers/BasicTower.h"
#include <vector>
#include "../Classes/UI/StoreUI.h"

class Level_1 : public cocos2d::Scene
{
private:
	static Level_1 * singleton;
	float cooldown = 0;
	int waveCount = 15;
	cocos2d::Node * enemies;
	void BuyTower(Ref * sender);
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
	cocos2d::Size resolution;
	StoreUI * storeUI;
public:
    static cocos2d::Scene* createScene();
	static Level_1 * GetInstance();
    virtual bool init();
	void GameOver(bool lose);
    CREATE_FUNC(Level_1);
    void update(float dt);
};



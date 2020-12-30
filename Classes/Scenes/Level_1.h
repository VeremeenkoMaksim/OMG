#pragma once
#include "cocos2d.h"
#include "Economy.h"
#include <vector>
#include "../Classes/UI/StoreUI.h"
#include "../Classes/Json/JsonInstance.h"

class Level_1 : public cocos2d::Scene
{
private:
	static Level_1 * singleton;
	float enemiesCooldown = 0;
	float wavesCooldown = 0;
	cocos2d::Node * enemies;
	void BuyTower(Ref * sender);
	bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event);
	cocos2d::Size resolution;
	StoreUI * storeUI;
	nlohmann::json data;
	int waveCount = 1;
	int wavePartCount = 1;
	int enemiesCount = 0;
	bool waveStarted = false;
	void StartWave(Ref * sender);
	MenuItemImage * startWaveBtn;
public:
	Economy * economy;
    static cocos2d::Scene* createScene();
	static Level_1 * GetInstance();
    virtual bool init();
	void GameOver(bool lose);
    CREATE_FUNC(Level_1);
    void update(float dt);
};



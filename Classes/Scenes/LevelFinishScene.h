#pragma once
#ifndef __LEVELFINISH_SCENE_H__
#define __LEVELFINISH_SCENE_H__

#include "cocos2d.h"

class LevelFinish : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    void RestartLevel(cocos2d::Ref* pSender);
    void GoToMainMenu(cocos2d::Ref* pSender);
    void CloseGame(cocos2d::Ref* pSender);

    bool lose;
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(LevelFinish);
};

#endif
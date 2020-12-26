#include "MainMenu.h"
#include "Level_1.h"
#include <cstring>

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

bool MainMenu::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto director = cocos2d::Director::getInstance();

    auto visibleSize = director->getVisibleSize();
    Vec2 origin = director->getVisibleOrigin();
    director->setProjection(Director::Projection::_2D);
    /* musicID = AudioEngine::play2d("audio/music/main_menu.mp3", false);
    AudioEngine::setVolume(musicID, 0.08);*/

    /*auto title = Sprite::create();
    char str[200] = { 0 };
    auto spriteCache = SpriteFrameCache::getInstance();
    spriteCache->addSpriteFramesWithFile("res/menu/main_title.plist");
    Vector<SpriteFrame*> titleAnimFrames(6);

    for (int i = 1; i <= 6; i++)
    {
        sprintf(str, "main_title_%i.png", i);
        auto frame = spriteCache->getSpriteFrameByName(str);
        frame->getTexture()->setAliasTexParameters();
        titleAnimFrames.pushBack(spriteCache->getSpriteFrameByName(str));
    }
    auto titleAnimation = Animation::createWithSpriteFrames(titleAnimFrames, 0.074);
    Animate* titleAnimate = Animate::create(titleAnimation);
    title->getTexture()->setAliasTexParameters();
    title->setScale(3.5 * 5);
    title->setAnchorPoint(Vec2(0.5, 0.5));
    title->setPosition(Vec2(visibleSize.width / 2 + origin.x, origin.y + visibleSize.height / 4 * 3));
    title->runAction(RepeatForever::create(titleAnimate));

    this->addChild(title, 1);*/

    auto continueLabel = Label::createWithTTF("CONTINUE", "fonts/PixelForce.ttf", 18);
    auto startLabel = Label::createWithTTF("START NEW GAME", "fonts/PixelForce.ttf", 18);
    auto levelsLabel = Label::createWithTTF("CHOOSE LEVEL", "fonts/PixelForce.ttf", 18);
    auto exitLabel = Label::createWithTTF("EXIT", "fonts/PixelForce.ttf", 18);

    MenuItemLabel* continueItem = MenuItemLabel::create(continueLabel, CC_CALLBACK_1(MainMenu::ContinueGame, this));
    continueItem->setEnabled(false);

    MenuItemLabel* startItem = MenuItemLabel::create(startLabel, CC_CALLBACK_1(MainMenu::GoToNewGameScene, this));
    //MenuItemLabel* levelsItem = MenuItemLabel::create(levelsItem, CC_CALLBACK_1(MainMenu::GoToLevelChooseScene, this));

    MenuItemLabel* exitItem = MenuItemLabel::create(exitLabel, CC_CALLBACK_1(MainMenu::CloseGame, this));

    auto menu = Menu::create(continueItem, startItem, /*levelsItem,*/ exitItem, NULL);
    menu->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 3));
    menu->alignItemsVerticallyWithPadding(10);
    this->addChild(menu, 1);

    return true;
}

void MainMenu::GoToNewGameScene(cocos2d::Ref* pSender) {
   auto scene = Level_1::createScene();
   Director::getInstance()->replaceScene(scene);
}

void MainMenu::ContinueGame(cocos2d::Ref* pSender) {
    /*audioengine::stopall();
    audioengine::end();*/
    auto scene = Level_1::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(2, scene));
}

//void MainMenu::GoToLevelChooseScene(cocos2d::Ref* pSender) {
//    auto scene = LevelChoose::createScene();
//    Director::getInstance()->replaceScene(scene);
//}

void MainMenu::CloseGame(cocos2d::Ref* pSender) {
    /*AudioEngine::stopAll();
    AudioEngine::end();*/
    Director::getInstance()->end();
}
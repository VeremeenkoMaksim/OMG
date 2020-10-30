#include "Level_1.h"

USING_NS_CC;

Scene* Level_1::createScene()
{
    return Level_1::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
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

  
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("backgrounds/bg_level_1.jpg");
    sprite->setScale(0.55f,0.55f);
    if (sprite == nullptr)
    {
        problemLoading("'backgrounds/bg_level_1.jpg'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }

    this->scheduleUpdate();
    return true;
}

void Level_1::update(float dt) {
    
}

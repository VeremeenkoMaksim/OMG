#include "cocos2d.h"

class TTile:public cocos2d::Node {
private:
	cocos2d::Vec2 tilePos;
public: 
	TTile(cocos2d::Vec2 tilePos);
	void setSprite(cocos2d::Sprite *sprite, int layer);
	cocos2d::Vec2 GetTilePos();
};
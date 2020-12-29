#include "cocos2d.h"
#include "../Classes/towers/Tower.h"
class TTile : public cocos2d::Node {

private:
	cocos2d::Vec2 tilePos;
	Tower* tower;
	cocos2d::Sprite * obstacle;
public: 
	bool empty = true;
	TTile(cocos2d::Vec2 tilePos);
	void setSprite(cocos2d::Sprite *sprite, int layer);
	cocos2d::Vec2 GetTilePos();
	void SetTower(Tower* tower);
	Tower* GetTower();
	void SetObstacle(cocos2d::Sprite * obstacle);
	cocos2d::Sprite * GetObstacle();
};
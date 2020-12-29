#include "Tile.h"

TTile::TTile(cocos2d::Vec2 tilePos) {
	this->tilePos = tilePos;
}

void TTile::setSprite(cocos2d::Sprite *sprite, int layer) {
	this->addChild(sprite, layer);
}

cocos2d::Vec2 TTile::GetTilePos() {
	return tilePos;
}

void TTile::SetTower(Tower* tower) {
	empty = false;
	this->tower = tower;
}
Tower * TTile::GetTower() {
	return tower;
}
void TTile::SetObstacle(cocos2d::Sprite * obstacle) {
	empty = false;
	this->obstacle = obstacle;
}
cocos2d::Sprite * TTile::GetObstacle() {
	return obstacle;
}
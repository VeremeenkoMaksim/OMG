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
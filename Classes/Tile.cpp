#include "Tile.h"

void TTile::setSprite(cocos2d::Sprite *sprite, int layer) {
	this->addChild(sprite, layer);
}
#include "Field.h"
#include <fstream>
Field* Field::CreateField(int width, int height) {
	tiles = new TTile**[height];
	std::string ** typesTile = GetDataField();
	for (auto i = 0; i < height; i++) {
		tiles[i] = new TTile*[width];
	}
	int resolutionX = 1024;
	int resolutionY = 768;
	int tileSize = 76;
	float offsetX = (resolutionX - width * tileSize) / 2;
	float offsetY = (resolutionY - height * tileSize) / 2;
	for (auto i = 0; i < height; i++) {
		for (auto j = 0; j < width; j++) {
			tiles[i][j] = new TTile();
			tiles[i][j]->addChild(cocos2d::Sprite::create("backgrounds/field/tiles/" + typesTile[i][j]+".jpg"), 10);
			tiles[i][j]->setPosition(tileSize/2 + offsetX + tileSize * j, tileSize/2 + offsetY + tileSize * i);
			this->addChild(tiles[i][j], 0);
		}
	}
	return this;
}

std::string ** Field::GetDataField() {
	std::ifstream fin("../Resources/backgrounds/field/level_1.txt");
	fin >> width;
	fin >> height;
	std::string ** values = new std::string*[height];
	for (auto i = 0; i < height; i++) {
		values[i] = new std::string[width];
	}
	for (auto i = height-1; i >= 0; i--) {
		for (auto j = 0; j < width; j++) {
			fin >> values[i][j];
		}
	}
	return values;
}
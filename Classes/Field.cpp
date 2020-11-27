#pragma once
#include "Field.h"
#include <fstream>

Field* Field::singleton = 0;
Field::Field() {
	dataField = JsonInstance::GetInstance()->GetData("field");
	int resolutionX = cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize().width;
	dataResolution = JsonInstance::GetInstance()->GetData("resolutions")[std::to_string(resolutionX)];
	if (dataResolution.empty()) {
		dataResolution = JsonInstance::GetInstance()->GetData("resolutions")["1024"];
	}
}
Field* Field::GetInstance() {
	if (!singleton) {
		singleton = new Field();
	}
	return singleton;
}

Field* Field::CreateField(int width, int height) {
	tiles = new TTile**[height];
	std::string ** typesTile = GetDataField();
	for (auto i = 0; i < height; i++) {
		tiles[i] = new TTile*[width];
	}
	int resolutionX = cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize().width;
	int resolutionY = cocos2d::Director::getInstance()->getOpenGLView()->getFrameSize().height;
	cocos2d::Size tileSize = cocos2d::Size(dataResolution["Tile"]["Width"], dataResolution["Tile"]["Height"]);
	float offsetX = (resolutionX - width * tileSize.width) / 2;
	float offsetY = (resolutionY - height * tileSize.height) / 2;
	for (auto i = 0; i < height; i++) {
		for (auto j = 0; j < width; j++) {
			tiles[i][j] = new TTile(cocos2d::Vec2(j,i));
			tiles[i][j]->addChild(cocos2d::Sprite::create(dataField["Tiles"][typesTile[i][j]]), 10);
			tiles[i][j]->setPosition(tileSize.width/2 + offsetX + tileSize.width * j, tileSize.height/2 + offsetY + tileSize.height * i);
			if (typesTile[i][j] == "1") {
				fullWay.push_back(tiles[i][j]);
			}
			this->addChild(tiles[i][j], 0);
		}
	}
	SetTheWay();
	return this;
}

std::string ** Field::GetDataField() {
	std::ifstream fin((std::string) dataField["Levels"]["Level_1"]);
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
	fin.close();
	return values;
}

std::vector<TTile*> Field::GetTheWay() {
	return way;
}
void Field::SetTheWay() {
	std::ifstream fin((std::string) dataField["Ways"]["Level_1"]);
	while (!fin.eof()) {
		auto i = 0;
		auto j = 0;
		fin >> i;
		// -1 in the level_1_way.txt, indicates that the way should be searched automatically
		// Also in the level_1_way.txt below there should be a line with the starting position
		if (i == -1) {
			fin >> i;
			fin >> j;
			AutoSetTheWay(cocos2d::Vec2(j,i));
			
			break;
		}
		fin >> j;
		way.push_back(tiles[i][j]);
	}
}
// Automatically detect the nodes in the way
void Field::AutoSetTheWay(cocos2d::Vec2 startPosition) {
	fullWay = sortFullWay(fullWay, startPosition);
	way.push_back(fullWay[0]);
	bool byX;
	if (fullWay[1]->getPosition().y - fullWay[0]->getPosition().y != 0) {
		byX = false;
	}
	else byX = true;

	for (auto i = 2; i < fullWay.size(); i++) {
		if (byX && fullWay[i-1]->getPosition().y - fullWay[i]->getPosition().y != 0) {
			way.push_back(fullWay[i-1]);
			byX = false;
		}
		if (!byX && fullWay[i - 1]->getPosition().x - fullWay[i]->getPosition().x != 0) {
			way.push_back(fullWay[i-1]);
			byX = true;
		}
	}
	way.push_back(fullWay[fullWay.size()-1]);
}
std::vector<TTile*> Field::sortFullWay(std::vector<TTile*> fullWay, cocos2d::Vec2 startPosition) {
	std::vector<TTile*> sortedVector;
	int sizeFullWay = fullWay.size();

	auto lastTile = tiles[(int)startPosition.y][(int)startPosition.x];
	sortedVector.push_back(lastTile);
	fullWay.erase(std::remove(fullWay.begin(), fullWay.end(), lastTile), fullWay.end());

	while (sortedVector.size() < sizeFullWay) {
		for (auto i = 0; i < fullWay.size(); i++) {
			if (TilesIsNeighbors(fullWay[i], lastTile)) {
				lastTile = fullWay[i];
				sortedVector.push_back(lastTile);
				fullWay.erase(std::remove(fullWay.begin(), fullWay.end(), lastTile), fullWay.end());
			}
		}
	}
	return sortedVector;
}

bool Field::TilesIsNeighbors(TTile * tile1, TTile * tile2) {
	return abs(tile1->GetTilePos().x - tile2->GetTilePos().x) == 1 && abs(tile1->GetTilePos().y - tile2->GetTilePos().y) == 0 ||
		abs(tile1->GetTilePos().x - tile2->GetTilePos().x) == 0 && abs(tile1->GetTilePos().y - tile2->GetTilePos().y) == 1;
}

void Field::
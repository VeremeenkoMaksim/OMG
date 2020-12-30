#include "StoreUI.h"
#include "../Classes/json/JsonInstance.h"
#include "Field.h"

USING_NS_CC;

StoreUI * StoreUI::Create() {
	auto instance = new StoreUI();
	auto dataUI = JsonInstance::GetInstance()->GetData("UI")["Store"];
	auto dataTowers = JsonInstance::GetInstance()->GetData("towers");

	auto bg = Sprite::create(dataUI["BgImage"]);
	auto resolution = Director::getInstance()->getVisibleSize();

	bg->setPosition(resolution.width+100, resolution.height/2);
	instance->addChild(bg);
	int count = 1;
	
	Vector<MenuItem*> menuItems;

	while (dataUI["Content"].contains(std::to_string(count))) {
		auto spriteFrame = Sprite::create(dataUI["FrameImage"]);
		spriteFrame->setPosition(56 + 86 * ((count - 1) % 2), 430 - 86* ((count - 1) / 2));
		bg->addChild(spriteFrame);

		std::string nameOfTower = dataUI["Content"][std::to_string(count)]["Type"];

		auto towerBtn = MenuItemImage::create(dataTowers[nameOfTower]["Image"], dataTowers[nameOfTower]["Image"], CC_CALLBACK_1(StoreUI::TowerButton, instance, nameOfTower));
		menuItems.pushBack(towerBtn);
		towerBtn->setPosition(56 + 86 * ((count - 1) % 2), 430 - 86 * ((count - 1) / 2));
		towerBtn->setScale(dataTowers[nameOfTower]["Scale"]);
		//spriteFrame->addChild(towerBtn);
		
		
		count++;
	}
	auto menu = Menu::createWithArray(menuItems);
	menu->setPosition(Point::ZERO);
	bg->addChild(menu);

	return instance;
}

void StoreUI::OpenStore() {
	if (!opened) {
		opened = true;
		auto action = MoveBy::create(0.2, Vec2(-200, 0));
		this->runAction(action);
	}
}

void StoreUI::CloseStore() {
	if (opened) {
		opened = false;
		auto action = MoveBy::create(0.2, Vec2(200, 0));
		this->runAction(action);
	}
}

void StoreUI::TowerButton(Ref * sender, std::string nameOfTower) {
	if (nameOfTower == "BasicTower") {
		building = true;
		buildingTower = nameOfTower;
		CloseStore();
		Field::GetInstance()->DrawGrid();
	}
}
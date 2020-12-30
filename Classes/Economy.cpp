#include "Economy.h"
USING_NS_CC;

Economy::Economy(int gold) {
	this->gold = gold;
}

void Economy::AddGold(int gold) {
	this->gold += gold;
	goldAmountText->setString(std::to_string(this->gold));
}

void Economy::DeductGold(int gold) {
	if (gold > this->gold) {
		this->gold = 0;
	}
	else {
		this->gold -= gold;
	}
	goldAmountText->setString(std::to_string(this->gold));
}

int Economy::GetGolgAmount() {
	return gold;
}
Node * Economy::CreateUIGold() {
	auto goldUI = Node::create();
	auto goldImage = Sprite::create("UI/images/gold.png");
	goldImage->setPosition(50, Director::getInstance()->getVisibleSize().height - 50);
	goldImage->setScale(0.35);
	goldUI->addChild(goldImage);
	goldAmountText = Label::create();
	goldAmountText->setString(std::to_string(gold));
	goldAmountText->setSystemFontSize(20);
	goldAmountText->setPosition(100, Director::getInstance()->getVisibleSize().height - 50);
	goldUI->addChild(goldAmountText);
	return goldUI;
}
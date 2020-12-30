#include "cocos2d.h"
USING_NS_CC;

class Economy {

private:
	int gold;
	Label * goldAmountText;
public:
	Economy(int gold);
	void AddGold(int gold);
	void DeductGold(int gold);
	Node * CreateUIGold();
	int GetGolgAmount();
};
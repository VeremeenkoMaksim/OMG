#include "cocos2d.h"
USING_NS_CC;
class StoreUI : public Node {

private:
	
public: 
	bool opened = false;
	static StoreUI * Create();
	void OpenStore();
	void CloseStore();
	void TowerButton(Ref * sender, std::string nameOfTower);
	bool building = false;
	std::string buildingTower;
};
#include "cocos2d.h"
#include "../Classes/json/JsonInstance.h"
class MainHouse : public cocos2d::Node {
private: 
	static MainHouse* singleton;
	float health;
	cocos2d::Label *label;
	nlohmann::json data;
	cocos2d::Sprite* sprite;
public:
	void ReceiveDamage(float damage);
	virtual bool init();
	MainHouse();
	static MainHouse* GetInstance();
};
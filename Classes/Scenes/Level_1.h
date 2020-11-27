#include "cocos2d.h"

class Level_1 : public cocos2d::Scene
{
private:
	void imgui();
    cocos2d::Node* enemies;
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
     CREATE_FUNC(Level_1);

     void update(float dt);
};



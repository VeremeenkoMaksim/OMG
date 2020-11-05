#include "cocos2d.h"
#include "Tile.h"
#include "cocos2d.h"

class Field : public cocos2d::Node
{
private:
	TTile *** tiles;
	int width;
	int height;
	std::string** getDataField();
public:
	Field* createField(int width, int height);

};
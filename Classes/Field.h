#include "cocos2d.h"
#include "Tile.h"

class Field : public cocos2d::Node
{
private:
	TTile *** tiles;
	int width;
	int height;
	std::string** GetDataField();
public:
	Field* CreateField(int width, int height);

};
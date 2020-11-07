#include "cocos2d.h"
#include "Tile.h"
#include <vector>

class Field : public cocos2d::Node
{
private:
	int width;
	int height;
	std::string** GetDataField();
	static Field * singleton;
	std::vector<TTile*> way = {};
	void SetTheWay();
	void AutoSetTheWay();
public:
	TTile *** tiles;
	Field * CreateField(int width, int height);
	static Field * GetInstance();
	std::vector<TTile*> GetTheWay();
};
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
	std::vector<TTile*> fullWay = {};
	void SetTheWay();
	void AutoSetTheWay(cocos2d::Vec2 startPosition);
	std::vector<TTile*> sortFullWay(std::vector<TTile*> fullWay, cocos2d::Vec2 startPosition);
	bool TilesIsNeighbors(TTile * tile1, TTile * tile2);
public:
	TTile *** tiles;
	Field * CreateField(int width, int height);
	static Field * GetInstance();
	std::vector<TTile*> GetTheWay();
};
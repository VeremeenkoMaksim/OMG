#pragma once
#include "json.hpp"
#include <string>

class JsonInstance {
	
private: 	
	nlohmann::json enemiesData;
	nlohmann::json towersData;
	nlohmann::json fieldData;
	nlohmann::json resolutionsData;
	nlohmann::json projectilesData;
	nlohmann::json UIData;

	static JsonInstance * singleton;
public:
	static JsonInstance * GetInstance();
	JsonInstance();
	nlohmann::json GetData(std::string nameOfData);

};

#pragma once
#include "JsonInstance.h"
#include <fstream>

JsonInstance * JsonInstance::singleton = 0;

JsonInstance::JsonInstance() {
	std::ifstream fin("../Resources/enemies/data.json");
	enemiesData = nlohmann::json::parse(fin);
	fin.close();

	fin.open("../Resources/field/data.json");
	fieldData = nlohmann::json::parse(fin);
	fin.close();

	fin.open("../Resources/resolutions.json");
	resolutionsData = nlohmann::json::parse(fin);
	fin.close();

	fin.open("../Resources/towers/data.json");
	towersData = nlohmann::json::parse(fin);
	fin.close();

}

JsonInstance * JsonInstance::GetInstance() {
		if (!singleton) {
			singleton = new JsonInstance();
		}
		return singleton;
}

nlohmann::json JsonInstance::GetData(std::string nameOfData) {
	if (nameOfData._Equal("enemies")) {
		return enemiesData;
	}
	else if (nameOfData._Equal("field")) {
		return fieldData;
	}
	else if (nameOfData._Equal("resolutions")) {
		return resolutionsData;
	}

	else if (nameOfData._Equal("towers")) {
		return towersData;
	}

	else return nullptr;
}



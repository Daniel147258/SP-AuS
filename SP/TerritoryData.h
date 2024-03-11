#pragma once
#include <string>
#include <functional>
#include "TerritorialUnit.h"
#include "State.h"
#include "Region.h"
#include "SOORP.h"
#include "Village.h"
#include "TerritorialUnit.h"
#include <vector>

class TerritoryData {

private:
	State& state_;
	std::vector<TerritorialUnit*> regions_;
	std::vector<TerritorialUnit*> soorps_;
	std::vector<TerritorialUnit*> villages_;

public:

	TerritoryData(State& state) : state_(state)
	{

	}

	~TerritoryData() {
		
		for (auto r : regions_)
		{
			delete r;
			r = nullptr;
		}
		regions_.clear();

		for (auto s : soorps_)
		{
			delete s;
			s = nullptr;
		}
		soorps_.clear();

		for (auto v : villages_)
		{
			delete v;
			v = nullptr;
		}
		villages_.clear();

	}

	void addRegion(Region* region) {
		regions_.push_back(region);
	}

	void addSOORP(SOORP* soorp) {
		soorps_.push_back(soorp);
	}

	void addVillage(Village* village) {
		villages_.push_back(village);
	}

	void printAllData() {
		std::cout << "---------------------------------------------------" << std::endl;
		std::cout << "Regions:" << std::endl;
		for (auto a : regions_) {
			std::cout << "Name: " << a->getName() << ", Code: " << a->getCode() << ", Type: " << a->getTeritoryType() << std::endl;
		}
		std::cout << "---------------------------------------------------" << std::endl;
		std::cout << "SOORPs:" << std::endl;
		for (auto a : soorps_) {
			std::cout << "Name: " << a->getName() << ", Code: " << a->getCode() << ", Type: " << a->getTeritoryType() << std::endl;
		}

		std::cout << "---------------------------------------------------" << std::endl;
		std::cout << "Villages:" << std::endl;
		for (auto a : villages_) {
			std::cout << "Name: " << a->getName() << ", Code: " << a->getCode() << ", Type: " << a->getTeritoryType() << std::endl;
		}
	}


};

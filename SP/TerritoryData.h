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
#include "Algorithms.h"

class TerritoryData {

private:
	State& state_;
	std::vector<TerritorialUnit*> regions_;
	std::vector<TerritorialUnit*> soorps_;
	std::vector<TerritorialUnit*> villages_;
	Algorithms<TerritorialUnit*, std::vector<TerritorialUnit*>::iterator >* alg_;
	std::vector<TerritorialUnit*> sortedData;
	// Sluzi na tredenie dat
	bool allow_;

public:

	TerritoryData(State& state) : state_(state)
	{
		alg_ = new Algorithms<TerritorialUnit*, std::vector<TerritorialUnit*>::iterator >();;
		allow_ = false;
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

		sortedData.clear();

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
		std::cout << "---------------------------------------------------" << std::endl;
		std::cout << "Villages:" << std::endl;
		for (auto a : villages_) {
			std::cout << "Name: " << a->getName() << ", Code: " << a->getCode() << ", Type: " << a->getTeritoryType() <<
				", Population: " << dynamic_cast<Village*>(a)->getNumberOfPeople() << std::endl;
		}
	}

	void printVillages() {
		std::cout << "---------------------------------------------------" << std::endl;
		std::cout << "Villages:" << std::endl;
		for (auto a : villages_) {
			std::cout << "Name: " << a->getName() << ", Code: " << a->getCode() << ", Type: " << a->getTeritoryType() <<
				", Population: " << dynamic_cast<Village*>(a)->getNumberOfPeople() << std::endl;
		}
	}

	void printRegions() {
		std::cout << "---------------------------------------------------" << std::endl;
		std::cout << "Regions:" << std::endl;
		for (auto a : regions_) {
			std::cout << "Name: " << a->getName() << ", Code: " << a->getCode() << ", Type: " << a->getTeritoryType() << std::endl;
		}
	}

	void printSoorps() {
		std::cout << "---------------------------------------------------" << std::endl;
		std::cout << "SOORPs:" << std::endl;
		for (auto a : soorps_) {
			std::cout << "Name: " << a->getName() << ", Code: " << a->getCode() << ", Type: " << a->getTeritoryType() << std::endl;
		}
	}

	void printVillageInformation(std::string& nameOfVillage) {
		bool find = false;
		for (auto a : villages_) {
			if (nameOfVillage == a->getName()) {
				a->toString();
				find = true;
				break;
			}
		}
		if (!find) {
			std::cout << nameOfVillage << " Village wasn't found\n";
		}
	}

	void printSorted() {
		std::cout << "\n----------------------------------------\nSorted Data:\n";
		if (!sortedData.empty()) {
			for (auto& a : sortedData)
			{
				std::cout << a->toString();
				std::cout << "\n----------------------------------------\n";
			}
		}
		else {
			std::cout << "Nothing wasn't find\n----------------------------------------\n";
		}
	}

	void findVillagesByName(std::function<bool(const std::string&)> predicate) {
		if (!allow_) {
			sortedData.clear();
			sortedData = alg_->filterGetName<const std::string&>(villages_.begin(), villages_.end(), predicate);
		}
		else {
			std::vector<TerritorialUnit*> local = alg_->filterGetName<const std::string&>(villages_.begin(), villages_.end(), predicate);
			for (auto& a : local) {
				sortedData.push_back(a);
			}
			local.clear();
		}
	}

	void findRegionsByName(std::function<bool(const std::string&)> predicate) {
		if (!allow_) {
			sortedData.clear();
			sortedData = alg_->filterGetName<const std::string&>(regions_.begin(), regions_.end(), predicate);
		}
		else {
			std::vector<TerritorialUnit*> local = alg_->filterGetName<const std::string&>(regions_.begin(), regions_.end(), predicate);
			for (auto& a : local) {
				sortedData.push_back(a);
			}
			local.clear();
		}
	}

	void findSoorpsByName(std::function<bool(const std::string&)> predicate) {
		if (!allow_) {
			sortedData.clear();
			sortedData = alg_->filterGetName<const std::string&>(soorps_.begin(), soorps_.end(), predicate);
		}
		else {
			std::vector<TerritorialUnit*> local = alg_->filterGetName<const std::string&>(soorps_.begin(), soorps_.end(), predicate);
			for (auto& a : local) {
				sortedData.push_back(a);
			}
			local.clear();
		}
	}

	void findAllByName(std::function<bool(const std::string&)> predicate) {
		allow_ = true;
		findRegionsByName(predicate);
		findSoorpsByName(predicate);
		findVillagesByName(predicate);
		allow_ = false;
	}
};

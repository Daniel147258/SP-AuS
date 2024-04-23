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
#include <libds/heap_monitor.h>

class TerritoryData {

private:
	State& state_;
	std::vector<TerritorialUnit*> regions_;
	std::vector<TerritorialUnit*> soorps_;
	std::vector<TerritorialUnit*> villages_;
	Algorithms* alg_;
	std::vector<TerritorialUnit*> sortedData;
	// Sluzi na tredenie dat
	bool allow_;

public:

	TerritoryData(State& state) : state_(state)
	{
		alg_ = new Algorithms();
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

		delete alg_;
		state_.~State();

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

	template<typename IteratorType>
	void find(IteratorType begin, IteratorType end, std::function<bool(TerritorialUnit*)> predicate) {
		sortedData = alg_->filter<TerritorialUnit*, TerritorialUnit*, IteratorType>(begin, end, predicate);
	}

	const std::vector<TerritorialUnit*>& getRegions() const {
		return regions_;
	}

	const std::vector<TerritorialUnit*>& getSoorps() const {
		return soorps_;
	}

	const std::vector<TerritorialUnit*>& getVillages() const {
		return villages_;
	}

	void clearSortedData() {
		sortedData.clear();
	}
};

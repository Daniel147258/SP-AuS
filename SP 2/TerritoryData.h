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
#include <libds/amt/explicit_hierarchy.h>

using MuT = ds::amt::MultiWayExplicitHierarchy<TerritorialUnit*>;
using Block = ds::amt::MultiWayExplicitHierarchyBlock<TerritorialUnit*>;

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
	//Viac cestna hierarchia
	MuT* hierarchy;


public:

	TerritoryData(State& state) : state_(state)
	{
		alg_ = new Algorithms<TerritorialUnit*, std::vector<TerritorialUnit*>::iterator >();
		allow_ = false;
		hierarchy = new MuT();
		hierarchy->emplaceRoot().data_ = &state_;
	}

	~TerritoryData() {
		delete hierarchy; // Malo by svetko co je v hierarchii vymazat pomocou post order 
		for (auto r : regions_)
		{
			if (r != nullptr) {
				delete r;
				r = nullptr;
			}
		}
		regions_.clear();

		for (auto s : soorps_)
		{
			if (s != nullptr) {
				delete s;
				s = nullptr;
			}
		}
		soorps_.clear();

		for (auto v : villages_)
		{
			if (v != nullptr) {
				delete v;
				v = nullptr;
			}
		}
		villages_.clear();

		sortedData.clear();

		delete alg_;
		//state_.~State(); to mazem uz vyssie

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

	void findVillages(std::function<bool(TerritorialUnit*)> predicate) {
		if (!allow_) {
			sortedData.clear();
			sortedData = alg_->filter<TerritorialUnit*>(villages_.begin(), villages_.end(), predicate);
		}
		else {
			std::vector<TerritorialUnit*> local = alg_->filter<TerritorialUnit*>(villages_.begin(), villages_.end(), predicate);
			for (auto& a : local) {
				sortedData.push_back(a);
			}
			local.clear();
		}
	}

	void findRegions(std::function<bool(TerritorialUnit*)> predicate) {
		if (!allow_) {
			sortedData.clear();
			sortedData = alg_->filter<TerritorialUnit*>(regions_.begin(), regions_.end(), predicate);
		}
		else {
			std::vector<TerritorialUnit*> local = alg_->filter<TerritorialUnit*>(regions_.begin(), regions_.end(), predicate);
			for (auto& a : local) {
				sortedData.push_back(a);
			}
			local.clear();
		}
	}

	void findSoorps(std::function<bool(TerritorialUnit*)> predicate) {
		if (!allow_) {
			sortedData.clear();
			sortedData = alg_->filter<TerritorialUnit*>(soorps_.begin(), soorps_.end(), predicate);
		}
		else {
			std::vector<TerritorialUnit*> local = alg_->filter<TerritorialUnit*>(soorps_.begin(), soorps_.end(), predicate);
			for (auto& a : local) {
				sortedData.push_back(a);
			}
			local.clear();
		}
	}

	void findInAllCategories(std::function<bool(TerritorialUnit*)> predicate) {
		allow_ = true;
		findRegions(predicate);
		findSoorps(predicate);
		findVillages(predicate);
		allow_ = false;
	}

	void addSon(Block* parent, Block* son) {
		parent->sons_->insertLast().data_ = son;
	}
	
	MuT& getHierarchy() {
		return *hierarchy;
	}
};

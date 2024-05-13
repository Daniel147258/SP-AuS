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
#include <libds/amt/explicit_hierarchy.h>
#include <libds/heap_monitor.h>
#include <libds/adt/table.h>
#include "MySequenceSortedTable.h"

using MuT = ds::amt::MultiWayExplicitHierarchy<TerritorialUnit*>;
using Block = ds::amt::MultiWayExplicitHierarchyBlock<TerritorialUnit*>;
using It = MuT::PreOrderHierarchyIterator;
class TerritoryData {


private:
	State& state_;
	std::vector<TerritorialUnit*> regions_;
	std::vector<TerritorialUnit*> soorps_;
	std::vector<TerritorialUnit*> villages_;
	Algorithms* alg_ = nullptr;
	std::vector<TerritorialUnit*> sortedData;
	// Sluzi na tredenie dat
	bool allow_;
	//Viac cestna hierarchia
	MuT* hierarchy = nullptr;
	MySequenceSortedTable* table;

public:

	TerritoryData(State& state) : state_(state)
	{
		alg_ = new Algorithms();
		allow_ = false;
		hierarchy = new MuT();
		table = new MySequenceSortedTable();
		
	}

	~TerritoryData() {

		delete table;

		if (hierarchy != nullptr) {
			delete hierarchy; // Malo by svetko co je v hierarchii vymazat pomocou post order 
			hierarchy = nullptr;
		}

		for (auto* r : regions_)
		{
			if (r != nullptr) {
				delete r;
				//r = nullptr;
			}
		}
		regions_.clear();

		for (auto* s : soorps_)
		{
			if (s != nullptr) {
				delete s;
				//s = nullptr;
			}
		}
		soorps_.clear();

		for (auto* v : villages_)
		{
			if (v != nullptr) {
				delete v;
				//v = nullptr;
			}
		}
		villages_.clear();

		sortedData.clear();

		if (alg_ != nullptr) {
			delete alg_;
			alg_ = nullptr;
		}



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
		std::cout << "\n----------------------------------------\nSorted Data(" << sortedData.size() << "):\n";
		if (!sortedData.empty()) {
			for (auto& a : sortedData)
			{
				std::cout << a->toString();
				std::cout << "\n----------------------------------------\n";
			}
			std::cout << "\nNumber of find data: " << sortedData.size() << "\n";
		}
		else {
			std::cout << "Nothing wasn't find\n----------------------------------------\n";
		}
	}


	void addSon(Block* parent, Block* son) {
		if (hierarchy->isRoot(*parent)) {
			hierarchy->accessRoot()->sons_->insertLast().data_ = son;
		}
		else {
			hierarchy->accessParent(*son)->sons_->insertLast().data_ = son;
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

	MuT& getHierarchy() {
		return *hierarchy;
	}

	TerritorialUnit& getState() {
		return state_;
	}

	void clearSortedData() {
		sortedData.clear();
	}

	MySequenceSortedTable* getTable() {
		return table;
	}

	void findItemInTable(std::string& key) {
		std::cout << "Find data:\n";
		if (table->findDataByKey(key) == nullptr) {
			std::cout << "Nothing was find\n";
		}
		else {
			ImplicitSequence* a = table->findDataByKey(key)->data_.data_;
			for (auto item = a->begin(); item != a->end(); ++item) {
				std::cout << (*item)->toString();
				std::cout << "\n-------------------------------------------\n";
			}
			
		}
		
	}
};

#pragma once
#include <string>
#include <functional>
#include <libds/adt/table.h>
#include "TerritoryData.h"

using ImplicitSequence = ds::amt::ImplicitSequence<TerritorialUnit*>;
using SortedSequenceTab = ds::adt::SortedSequenceTable<std::string, ImplicitSequence*>;

class MySequenceSortedTable : public SortedSequenceTab
{
private:
	SortedSequenceTab* table;
	
public: 
	MySequenceSortedTable() {
		table = new SortedSequenceTab();
	};

	~MySequenceSortedTable() {
		for (auto itemTable = table->begin(); itemTable != table->end(); ++itemTable)
		{
			for (auto itemSequence = 0; itemSequence < (*itemTable).data_->size(); ++itemSequence)
			{
				// Uzemne jednotky vymazujem v territory data
			}
			delete (*itemTable).data_;
		}
		delete table;
	};

	void addToTable(const std::string& key, TerritorialUnit* unit) {
		if (unit != nullptr && key.size() > 0) {
			if (table->findBlockWithKey(key) != nullptr) {
				ImplicitSequence* data = table->findBlockWithKey(key)->data_.data_;
				data->insertLast().data_ = unit;
				//std::cout << "Data was succesfully insert !\n";
			}

			else {
				ImplicitSequence* data = new ImplicitSequence();
				data->insertLast().data_ = unit;
				table->insert(key, data);
				//std::cout << "Data was succesfully insert !\n";
			}
		}
		else
		{
			//std::cout << "Data was not insert !!\n";
		}
	}

	auto* findDataByKey(std::string& key) {
		// Pozor na nulltptr !!!!
		return table->findBlockWithKey(key);
	}
};
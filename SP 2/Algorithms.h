#pragma once
#include <string>
#include <functional>
#include <vector>     
#include <type_traits>
#include <libds/amt/explicit_hierarchy.h>

using MuT = ds::amt::MultiWayExplicitHierarchy<TerritorialUnit*>;
using Block = ds::amt::MultiWayExplicitHierarchyBlock<TerritorialUnit*>;
using It = MuT::PreOrderHierarchyIterator;

class Algorithms {

private:


public:
	Algorithms()
	{
	}

	~Algorithms()
	{
	}

	template<typename Factor, typename Data, typename Iterator>
	std::vector<Data> filter(Iterator begin, Iterator end, std::function<bool(Factor)> predicate) {
		std::vector<Data> filteredUnits;
		 while(begin != end){ // PreOrderIterator takto nevie rozoznat
			if ((*begin) != nullptr) {
				if (predicate((*begin))) {
					filteredUnits.push_back((*begin));
				}
			}
			if constexpr (std::is_same_v<Iterator, It>) {
				if ((*begin) == (*end)) { // Toto neplati pre iterator vectora 
					break;
				}
			}
			++begin;
		}

		return filteredUnits;
	}

};
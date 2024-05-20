#pragma once
#include <string>
#include <functional>
#include <vector>     
#include <type_traits>
#include <libds/amt/explicit_hierarchy.h>
#include "TerritorialUnit.h">

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

	//Ked je predikat null tak vlozi vsetko
	template<typename Factor, typename Data, typename Iterator>
	std::vector<Data> filter(Iterator begin, Iterator end, std::function<bool(Factor)> predicate) {
		std::vector<Data> filteredUnits;
		while (begin != end) { // PreOrderIterator takto nevie rozoznat
			if ((*begin) != nullptr) {
				if (predicate == nullptr) {
					filteredUnits.push_back((*begin));
				}
				else {
					if (predicate((*begin))) {
						filteredUnits.push_back((*begin));
					}
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

	//Prebera triediaci algoritmus a podla neho to utriedi
	template<typename Factor, typename Data, typename Iterator, typename sortIterator>
	std::vector<Data> filterAndSort(Iterator begin, Iterator end, std::function<bool(Factor)> predicate, std::function<std::vector<Data>(sortIterator, sortIterator)> sortingPredicate) {
		std::vector<Data> filteredUnits = filter<Factor, Data, Iterator>(begin, end, predicate);

		if constexpr (std::is_same_v<sortIterator, It>) {
			return sortingPredicate(begin, end);
		}
		else {
			return sortingPredicate(filteredUnits.begin(), filteredUnits.end());
		}
		
	}

};
#pragma once
#include <string>
#include <functional>
#include <vector> 
#include <libds/heap_monitor.h>

template<typename Data, typename Iterator>
class Algorithms {

private:


public:
	Algorithms()
	{
	}

	~Algorithms()
	{
	}

	template<typename Factor>
	std::vector<Data> filter(Iterator begin, Iterator end, std::function<bool(Factor)> predicate) {
		std::vector<Data> filteredUnits;
		for (auto it = begin; it != end; ++it) {
			if (predicate((*it))) {
				filteredUnits.push_back((*it));
			}
		}

		return filteredUnits;
	}
};
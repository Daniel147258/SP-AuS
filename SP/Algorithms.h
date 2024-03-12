#pragma once
#include <string>
#include <functional>
#include <vector> 

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
	std::vector<Data> filterGetName(Iterator begin, Iterator end, std::function<bool(Factor)> predicate) {
		std::vector<Data> filteredUnits;
		for (auto it = begin; it != end; ++it) {
			if (predicate((*it)->getName())) {
				filteredUnits.push_back((*it));
			}
		}

		return filteredUnits;
	}

};
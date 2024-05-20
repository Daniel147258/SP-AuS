#pragma once
#include "TerritoryData.h"


class SortingAlgorithms 
{
    using MuT = ds::amt::MultiWayExplicitHierarchy<TerritorialUnit*>;
    using It = MuT::PreOrderHierarchyIterator;
private:
	
public:
    SortingAlgorithms() {};
	~SortingAlgorithms() = default;
#include <vector>
#include <functional>

    // Funkcny a zaroven nefunckne pre vacsinu aplikacie, kvoli pcotu udajov
    template<typename Data, typename Iterator, typename ComparatorValue>
    std::function<std::vector<Data>(Iterator, Iterator)> bubbleSort(std::function<bool(ComparatorValue, ComparatorValue)> comparator) {
        return [comparator](Iterator begin, Iterator end) -> std::vector<Data> {
            std::vector<Data> sortedUnits;
            if (begin != end) {
                if constexpr (std::is_same_v<Iterator, It>) {
                    sortedUnits = std::vector<Data>((*begin), (*end));
                }
                else {
                    sortedUnits = std::vector<Data>(begin, end);
                }
            }

            bool swapped;
            do {
                swapped = false;
                for (auto it = sortedUnits.begin(); it != sortedUnits.end() - 1; ++it) {
                    if (comparator(*it, *(it + 1))) {
                        std::swap(*it, *(it + 1));
                        swapped = true;
                    }
                }
            } while (swapped);

            return sortedUnits;
            };
    }

    template<typename Data, typename Iterator, typename ComparatorValue>
    std::function<std::vector<Data>(Iterator, Iterator)> quickSort(std::function<bool(ComparatorValue, ComparatorValue)> comparator) {
        return [comparator](Iterator begin, Iterator end) -> std::vector<Data> {
            std::vector<Data> sortedUnits;
            if (begin != end) {
                if constexpr (std::is_same_v<Iterator, It>) {
                    sortedUnits = std::vector<Data>((*begin), (*end));
                }
                else {
                    sortedUnits = std::vector<Data>(begin, end);
                }
            }

            // Implementacai rekurzivneho Quick sortu
            std::function<void(size_t, size_t)> quickSortRecursive;
            quickSortRecursive = [&](size_t min, size_t max) {

                Data pivot = sortedUnits[(min + (max - min) / 2)];
                size_t left = min;
                size_t right = max;
                do 
                {
                    while (left <= sortedUnits.size() - 1 && comparator(sortedUnits[left], pivot)) {
                        ++left;
                    }
                    while (right > 0 && comparator(pivot, sortedUnits[right])) {
                        right--;
                    }
                    if (left <= right) {
                        std::swap(sortedUnits[left], sortedUnits[right]);
                        left++;
                        if (right > 0)
                            right--;
                    }
                } while (left <= right);

                if (min < right)
                    quickSortRecursive(min, right);
                if (left < max)
                    quickSortRecursive(left, max);
            };

            quickSortRecursive(0, sortedUnits.size() - 1);
   
            return sortedUnits;
        };
    }

    //Dalsie mozne implementacie triediacich algoritmov... 
};
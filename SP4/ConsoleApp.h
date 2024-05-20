#pragma once
#include <string>
#include <functional>
#include "Reader.h" 
#include "TerritoryData.h" 
#include "HierarchyIterator.h"
#include "libds/amt/implicit_sequence.h"
#include "SortingAlgorithms.h"
#include <locale>
#include <regex>
#include <cctype>

class ConsoleApp {

private:
	bool end_;
	TerritoryData* td_;
	HierarchyIterator* it_ = nullptr;
	bool isAlsoHierarchy_ = false;
	Block* endIt_ = nullptr; // posledny block pri prehladavani nevymazovat 
	SortingAlgorithms* alg_ = new SortingAlgorithms();

	void baseOptions()
	{
		std::string chooseOption = "LOPASK";
		while (true)
		{
			if (end_)
				break;

			std::cout << "\n- Input 1 if you want write all Territories\n"
				<< "- Input 2 write only Regions\n"
				<< "- Input 3 write only SOORP\n"
				<< "- Input 4 write only Villages\n"
				<< "- Input 5 Search Territory by predicate\n";

			if (isAlsoHierarchy_) {
				std::cout << "- Input 6 Moving in Hierarchy\n";
			}
			std::cout << "- Input 7 For searching in table\n";
			std::cout << "- Input ~ if you want end application\n"
				<< "Choice: ";
			std::cin >> chooseOption;
			if (chooseOption == "1")
			{
				td_->printAllData();
			}
			else if (chooseOption == "2")
			{
				td_->printRegions();
			}
			else if (chooseOption == "3")
			{
				td_->printVillages();
			}
			else if (chooseOption == "4")
			{
				td_->printVillages();
			}
			else if (chooseOption == "5")
			{
				ConsoleApp::sorting();
			}
			else if (chooseOption == "6" && isAlsoHierarchy_)
			{
				ConsoleApp::hierarchy();
			}
			else if (chooseOption == "7" && isAlsoHierarchy_)
			{
				tableOption();
			}
			else if (chooseOption == "~")
			{
				end_ = true;
				break;
			}
			else {
				std::cout << "- Selected wrong option !!! \n\n";
			}
		}
	}

	void sorting()
	{
		bool succes = false;
		std::string chooseOption = "LOPASK";
		while (true)
		{
			if (end_)
				break;

			std::cout << "\n- Input 1 Search in all territories\n" <<
				"- Input 2 Search only Regions\n" <<
				"- Input 3 Search only SOORP\n" <<
				"- Input 4 Search only Villages\n" <<
				"- Input @ step back \n" <<
				"- Input ~ if you want end application\n" <<
				"Choice: ";
			std::cin >> chooseOption;

			if (chooseOption >= "1" && chooseOption <= "4") {
				while (true) {
					std::string chooseOption2 = "  ";
					if (end_)
						break;
					std::cout << "\n- Input 1 predicate StartWithStr\n" <<
						"- Input 2 predicate ContainsStr\n" <<
						"- Input @ step back \n" <<
						"- Input ~ if you want end application\n" <<
						"Choice: ";
					std::cin >> chooseOption2;

					if (chooseOption2 == "1") {
						std::cout << "Input pattern: ";
						std::cin >> chooseOption2;

						if (chooseOption == "1") {
							td_->find(td_->getRegions().begin(), td_->getRegions().end(), startWithStrPredicate(chooseOption2));
							td_->printSorted();
							td_->find(td_->getSoorps().begin(), td_->getSoorps().end(), startWithStrPredicate(chooseOption2));
							td_->printSorted();
							td_->find(td_->getVillages().begin(), td_->getVillages().end(), startWithStrPredicate(chooseOption2));
							td_->printSorted();
						}


						else if (chooseOption == "2") {
							td_->find(td_->getRegions().begin(), td_->getRegions().end(), startWithStrPredicate(chooseOption2));
						}

						else if (chooseOption == "3") {
							td_->find(td_->getSoorps().begin(), td_->getSoorps().end(), startWithStrPredicate(chooseOption2));
						}

						else if (chooseOption == "4") {
							td_->find(td_->getVillages().begin(), td_->getVillages().end(), startWithStrPredicate(chooseOption2));
						}

						if (chooseOption != "1") {
							td_->printSorted();
						}
						td_->clearSortedData();
					}

					else if (chooseOption2 == "2") {
						std::cout << "Input pattern: ";
						std::cin >> chooseOption2;


						if (chooseOption == "1") {
							td_->find(td_->getRegions().begin(), td_->getRegions().end(), containStrPredicate(chooseOption2));
							td_->printSorted();
							td_->find(td_->getSoorps().begin(), td_->getSoorps().end(), containStrPredicate(chooseOption2));
							td_->printSorted();
							td_->find(td_->getVillages().begin(), td_->getVillages().end(), containStrPredicate(chooseOption2));
							td_->printSorted();

						}

						else if (chooseOption == "2") {
							td_->find(td_->getRegions().begin(), td_->getRegions().end(), containStrPredicate(chooseOption2));
						}

						else if (chooseOption == "3") {
							td_->find(td_->getSoorps().begin(), td_->getSoorps().end(), containStrPredicate(chooseOption2));
						}

						else if (chooseOption == "4") {
							td_->find(td_->getVillages().begin(), td_->getVillages().end(), containStrPredicate(chooseOption2));
						}
						if (chooseOption != "1") {
							td_->printSorted();
						}

						td_->clearSortedData();
					}

					else if (chooseOption2 == "@") {
						break;
					}

					else if (chooseOption2 == "~") {
						end_ = true;
						break;
					}

					else {
						std::cout << "- Selected wrong option !!! \n\n";
					}
				}
			}
			else if (chooseOption == "@") {
				break;
			}
			else if (chooseOption == "~") {
				end_ = true;
				break;
			}

			else {
				std::cout << "- Selected wrong option !!! \n\n";
			}

		}

	}

	void hierarchy() {
		std::string chooseOption = "LOPASK";
		it_ = new HierarchyIterator(&td_->getHierarchy());
		while (!end_) {
			std::cout << "Your actual node is: ";
			std::cout << it_->getPointerBlock()->data_->getName();
			std::cout << "\n- Input 1. Go previous\n"
				<< "- Input 2. Go down\n"
				<< "- Input 3. Search By Predicate\n"
				<< "- Input 4. Search By Predicate and Sort\n"
				<< "- Input 5. Sort\n"
				<< "- Input 6. Write information about actual node\n"
				<< "- Input ~ To end application\n" <<
				"Choice:";
			std::cin >> chooseOption;
			if (chooseOption == "1")
			{
				it_->goPrevious();
			}
			else if (chooseOption == "2")
			{
				if (it_->getPointerBlock()->sons_->size() > 0) {
					while (!end_) {
						int i = 1;
						int index = 0;
						for (auto& element : *(it_->getPointerBlock()->sons_)) {
							if (i % 3 == 0) {
								std::cout << i << ". " << element->data_->getName() << " ||\n ";
							}
							else {
								std::cout << i << ". " << element->data_->getName() << " || ";
							}
							++i;
						}

						std::cout << "Input index of next Territorial Unit:";
						std::cin >> chooseOption;
						std::cout << "\n";
						if (chooseOption == "@") {
							break;
						}
						else if (chooseOption == "~") {
							end_ = true;
							break;
						}

						try {
							index = std::stoi(chooseOption);
						}
						catch (const std::invalid_argument&) {
							std::cout << "That was not number !!\n";
							continue;
						}

						if (0 <= (index - 1) && it_->getPointerBlock()->sons_->size() >= (index - 1)) {
							int a = index - 1;
							it_->goNext(a);
							break;
						}
						else {
							std::cout << "Wrong index!!\n";
						}
					}
				}
				else {
					std::cout << "Actual node dont have any sons, you cant go lower \n";
				}
			}
			else if (chooseOption == "3")
			{
				predicates(it_, false);
			}
			else if (chooseOption == "4")
			{
				predicates(it_, true);
			}
			else if (chooseOption == "5")
			{
				sortHierarchy(it_, nullptr);
			}
			else if (chooseOption == "6")
			{
				std::cout << "------------------------------------------------------------------------\n";
				std::cout << it_->getPointerBlock()->data_->toString() << "\n";
				std::cout << "------------------------------------------------------------------------\n";
			}
			else  if (chooseOption == "~") {
				end_ = true;
				break;
			}
			else if (chooseOption == "@") {
				break;
			}

		}

	}

	void predicates(HierarchyIterator* it, bool sorting) {
		while (!end_) {
			//Nastavenie iteratora

			std::string chooseOption = "  ";
			std::cout << "\n- Input 1 predicate StartWithStr\n" <<
				"- Input 2 predicate ContainsStr\n" <<
				"- Input 3 predicate HasType\n" <<
				"- Input @ step back \n" <<
				"- Input ~ if you want end application\n" <<
				"Choice: ";
			std::cin >> chooseOption;
			if (chooseOption == "1") {
				std::string chooseOption2 = "  ";
				std::cout << "Input starting characters: ";
				std::cin >> chooseOption2;
				//1.startStr, 2.containStr, 3.hasType
				if (!sorting) {
					processPreOrderPredicate(it->getPointerBlock(), this->startWithStrPredicate(chooseOption2), true);
				}
				else {
					sortHierarchy(it, this->startWithStrPredicate(chooseOption2));
					
				}
				td_->printSorted();
				td_->clearSortedData();
			}
			else if (chooseOption == "2") {
				std::string chooseOption2 = "  ";
				std::cout << "Input containnig characters: ";
				std::cin >> chooseOption2;
				if (!sorting) {
					processPreOrderPredicate(it->getPointerBlock(),  this->containStrPredicate(chooseOption2), true);
				}
				else {
					sortHierarchy(it, this->containStrPredicate(chooseOption2));
				}
				td_->printSorted();
				td_->clearSortedData();

			}
			else if (chooseOption == "3") {
				while (!end_) {
					std::string chooseOption2 = "  ";
					std::string type = "";
					std::cout << "Input 1. State \n"
						<< "Input 2. Region\n"
						<< "Input 3. Soorp\n"
						<< "Input 4. Village\n"
						<< "Input ~. End application\n"
						<< "Input @. Step back\nChoice:";

					std::cin >> chooseOption2;

					if (chooseOption2 == "1") {
						type = "State";
					}
					else if (chooseOption2 == "2") {
						type = "Region";
					}
					else if (chooseOption2 == "3") {
						type = "SOORP";
					}
					else if (chooseOption2 == "4") {
						type = "Village";
					}
					else if (chooseOption2 == "@") {
						break;
					}
					else if (chooseOption2 == "~") {
						end_ = true;
						break;
					}
					else {
						std::cout << "Wrong option\n";
						continue;
					}
					if (!sorting) {
						processPreOrderPredicate(it->getPointerBlock(), this->hasTypePredicate(type), true);
					}
					else {
						sortHierarchy(it, this->hasTypePredicate(type));
					}

					td_->printSorted();
					td_->clearSortedData();

				}
			}
			else if (chooseOption == "@") {
				break;
			}
			else if (chooseOption == "~") {
				end_ = true;
				break;
			}
			else {
				std::cout << "Wrong option\n";
			}
		}

	}

	void sortHierarchy(HierarchyIterator* it, std::function<bool(TerritorialUnit*)> predicate) {
		while (!end_) {
			std::string chooseOption = "  ";
			std::cout << "\n- Input 1 Aplhabetical comparator\n" <<
				"- Input 2 Consonant Count: comparator\n" <<
				"- Input @ step back \n" <<
				"- Input ~ if you want end application\n" <<
				"Choice: ";
			std::cin >> chooseOption;
			if (chooseOption == "1") {
				if (predicate != nullptr) {
					this->processPreOrderPredicateSort(it->getPointerBlock(), predicate, alg_->quickSort<TerritorialUnit*, std::vector<TerritorialUnit*>::iterator, TerritorialUnit* >(this->alphabeticalComparator()), true);
					td_->printSorted();
					td_->clearSortedData();
				}
				else {

					ds::amt::Hierarchy<Block>* hierarchy2 = dynamic_cast<ds::amt::Hierarchy<Block>*>(&td_->getHierarchy());
					It begin(hierarchy2, it->getPointerBlock());
					this->findLastBlockInHierarchy(it->getPointerBlock()); // najde posledny block a priradi ho do atributu endIt_
					It end(hierarchy2, endIt_); // Musim z poslendeho bloku urobit iterator

					// Musim pouzit iterator vectora lebo findAndSort pouziva find ktory vrati vector a nad tym sa vykona sort...
					auto sortingAlgorithm = alg_->quickSort<TerritorialUnit*, std::vector<TerritorialUnit*>::iterator, TerritorialUnit*>(this->alphabeticalComparator()); 
					td_->findAndSort(begin, end, nullptr, sortingAlgorithm);
					td_->printSorted();
					td_->clearSortedData();
				}
			}

			else if (chooseOption == "2") {
				if (predicate != nullptr) {
					this->processPreOrderPredicateSort(it->getPointerBlock(), predicate, alg_->quickSort<TerritorialUnit*, std::vector<TerritorialUnit*>::iterator, TerritorialUnit* >(this->compareConsonantCount()), true);
					td_->printSorted();
					td_->clearSortedData();
				}
				else {
					ds::amt::Hierarchy<Block>* hierarchy2 = dynamic_cast<ds::amt::Hierarchy<Block>*>(&td_->getHierarchy());
					It begin(hierarchy2, it->getPointerBlock());
					this->findLastBlockInHierarchy(it->getPointerBlock()); // najde posledny block a priradi ho do atributu endIt_
					It end(hierarchy2, endIt_); // Musim z poslendeho bloku urobit iterator
					auto sortingAlgorithm = alg_->quickSort<TerritorialUnit*, std::vector<TerritorialUnit*>::iterator, TerritorialUnit*>(this->compareConsonantCount());
					td_->findAndSort(begin, end, nullptr, sortingAlgorithm);
					td_->printSorted();
					td_->clearSortedData();
				}
			}

			else if(chooseOption == "@") {
				break;
			}

			else if (chooseOption == "~") {
				end_ = true;
				break;
			}
			else {
				std::cout << "Wrong option !\n";
			}
		}
	}



	void tableOption() {
		while (!end_) {
			std::string chooseOption;
			std::cout << "- If you want go back input @\nInput name of Territorial unit which you want find: ";
			std::cin >> chooseOption;
			if (chooseOption == "@") {
				break;
			}
			else if (chooseOption == "~") {
				end_ = true;
				break;
			}
			td_->findItemInTable(chooseOption);
		}
	}

public:

	ConsoleApp() {};

	~ConsoleApp()
	{
		delete td_;
		if (it_ != nullptr) {
			delete it_;
		}
		delete alg_;

	}

	void runApp() {
		State s("Èeská republika", "124a");
		td_ = new TerritoryData(s);
		end_ = false;
		std::cout << "- Welcome in application\n" << "- Read options and choose one of them.\n" << "- For step back input @\n" << "- For continue click enter\n";
		std::cin.ignore();
		Reader* r = new Reader();
		std::string path = "C:/Users/Daniel/source/repos/SP/CR-upravene.csv";
		std::string chooseOption = "LOPASK";
		while (!end_)
		{
			if (end_) {
				break;
			}

			std::cout << "- Input 1 if you want read Territorial Units from default file without hierarchy\n" <<
				"- Input 2 if you want read Territorial Units from default file with hierarchy\n" <<
				"- Input 3 if you want read your own file\n" <<
				"- Input 4 if you want read Territorial Units from default file with hierarchy and table\n" <<
				"- Input ~ if you want end application\n" <<
				"Choice: ";
			std::cin >> chooseOption;
			if (chooseOption == "1") {
				r->loadAllTerritoryData(path, td_);
				std::cout << "- Territories sucessfuly loaded\n";
				baseOptions();
			}
			else if (chooseOption == "2") {
				r->loadAllTerritoryDataToHierarchy(path, td_);
				std::cout << "- Territories sucessfuly loaded\n";
				isAlsoHierarchy_ = true;
				baseOptions();
			}
			else if (chooseOption == "3") {
				bool loaded = false;
				while (!loaded)
				{
					std::cout << "- Write path to file: ";
					std::cin >> chooseOption;
					if (chooseOption == "@") {
						break;
					}
					if (r->loadAllTerritoryData(chooseOption, td_)) {
						std::cout << "- Territories sucessfuly loaded\n";
						loaded = true;
						baseOptions();
					}

				}
			}
			else if (chooseOption == "4") {
				r->loadAllTerritoryDataToHierarchyAndTable(path, td_);
				std::cout << "- Territories sucessfuly loaded\n";
				isAlsoHierarchy_ = true;
				baseOptions();
			}
			else if (chooseOption == "~") {
				end_ = true;
				break;
			}
			else {
				std::cout << "- Selected wrong option !!!\n\n";
			}
		}
		std::cout << "- Application ended sucessfuly\n";
		delete r;
	}

	//Prehalda hierarchiu podla vrcholu a predikatu a parametru
	void processPreOrderPredicate(Block* node, std::function<bool(TerritorialUnit*)> predicate, bool first) {

		ds::amt::Hierarchy<Block>* hierarchy2 = dynamic_cast<ds::amt::Hierarchy<Block>*>(&td_->getHierarchy());
		MuT* h = &td_->getHierarchy();
		endIt_ = node;
		if (node != nullptr) {
			It begin(hierarchy2, node);
			size_t deg = h->degree(*node);
			size_t sonsprocessed = 0;
			size_t n = 0;
			while (sonsprocessed < deg) {
				Block* son = h->accessSon(*node, n);
				if (son != nullptr) {
					processPreOrderPredicate(son, predicate, false);
					++sonsprocessed;
				}
				++n;
			}

			if (first) {
				It end(hierarchy2, endIt_);
				td_->find(begin, end, predicate);
			}

		}
	}

	template<typename Data, typename Iterator>
	void processPreOrderPredicateSort(Block* node, std::function<bool(TerritorialUnit*)> predicate,  std::function<std::vector<Data>(Iterator, Iterator)> sortingAlgorithm, bool first) {
		ds::amt::Hierarchy<Block>* hierarchy2 = dynamic_cast<ds::amt::Hierarchy<Block>*>(&td_->getHierarchy());
		MuT* h = &td_->getHierarchy();
		endIt_ = node;
		if (node != nullptr) {
			It begin(hierarchy2, node);
			size_t deg = h->degree(*node);
			size_t sonsprocessed = 0;
			size_t n = 0;
			while (sonsprocessed < deg) {
				Block* son = h->accessSon(*node, n);
				if (son != nullptr) {
					processPreOrderPredicate(son, predicate, false);
					++sonsprocessed;
				}
				++n;
			}

			if (first) {
				It end(hierarchy2, endIt_);
				td_->findAndSort(begin, end, predicate, sortingAlgorithm);
			}

		}
	}

	template<typename Data, typename Iterator>
	void sort(Iterator begin, Iterator end, std::function<std::vector<Data>(Iterator, Iterator)> sortingAlgorithm) {
		td_->findAndSort(begin, end, nullptr, sortingAlgorithm);
	}

	void findLastBlockInHierarchy(Block* node) {
		ds::amt::Hierarchy<Block>* hierarchy2 = dynamic_cast<ds::amt::Hierarchy<Block>*>(&td_->getHierarchy());
		MuT* h = &td_->getHierarchy();
		endIt_ = node;
		if (node != nullptr) {
			It begin(hierarchy2, node);
			size_t deg = h->degree(*node);
			size_t sonsprocessed = 0;
			size_t n = 0;
			while (sonsprocessed < deg) {
				Block* son = h->accessSon(*node, n);
				if (son != nullptr) {
					findLastBlockInHierarchy(son);
					++sonsprocessed;
				}
				++n;
			}

		}
	}


	//Predikaty
	std::function<bool(TerritorialUnit*)> startWithStrPredicate(std::string& param) {
		auto startsWithPr = [param](TerritorialUnit* unit) {
			return unit->getName().substr(0, param.length()) == param;
			};
		return startsWithPr;
	}

	std::function<bool(TerritorialUnit*)> containStrPredicate(std::string& param) {
		auto containsStr = [param](TerritorialUnit* unit) {
			return unit->getName().find(param) != std::string::npos;
			};
		return containsStr;
	}

	std::function<bool(TerritorialUnit*)> hasTypePredicate(std::string& param) {
		auto hasType = [param](TerritorialUnit* unit) {
			return unit->getTeritoryType() == param;
			};
		return hasType;
	}

	//Comparatory

	std::function<bool(TerritorialUnit*, TerritorialUnit*)> alphabeticalComparator() {
		return [&](TerritorialUnit* a, TerritorialUnit* b) -> bool {

			return czechAlphabeticalCompare(a->getName(), b->getName());
		};
	}

	std::function<bool(TerritorialUnit*, TerritorialUnit*)> compareConsonantCount() {
		return [&](TerritorialUnit* a, TerritorialUnit* b) -> bool {
			
			int countA = countConsonants(a->getName());
			int countB = countConsonants(b->getName());
			return countA > countB;
			};
	}


	//Pomocne metody

	bool czechAlphabeticalCompare(const std::string& a, const std::string& b) {
		// zoberiem iba po ten kratsi retazec a bude porovnavat
		size_t minLength = (a.length() < b.length()) ? a.length() : b.length();
		for (size_t i = 0; i < minLength; ++i) {
			char ca = std::tolower(a[i]);
			char cb = std::tolower(b[i]);
			if (ca != cb) {
				// vymenoval som vsetky znaky abecedne
				static const std::string czechAlphabet = "aáAÁbBcCèÈdDïÏeéìEÉÌfFgGhHchChiIíIÍjJkKlLmMnNòÒoóOÓpPqQrøØsSšŠtTuúùUÚÙvVwWxXyýYÝzZžŽ";
				size_t indexA = czechAlphabet.find(ca);
				size_t indexB = czechAlphabet.find(cb);
				if (indexA != std::string::npos && indexB != std::string::npos) {
					return indexA < indexB;
				}
				else {
					return ca < cb;
				}
			}
		}
		// zvitazi kratsi retazec
		return a.length() < b.length();
	}

	int countConsonants(std::string str) {
		int count = 0;
		for (char c : str) {
			// Ak je znak písmeno a nie je samohlaska
			if (!isVowel(c)) {
				count++;
			}
		}
		return count;
	}

	bool isVowel(char c) {
		static const std::regex vowels("[aAÁeEÉiIÍoÓuUÚyYÝáéíóúýúù]", std::regex_constants::icase);
		return std::regex_match(std::string(1, c), vowels);
	}
	

};
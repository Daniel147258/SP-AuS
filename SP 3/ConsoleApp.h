#pragma once
#include <string>
#include <functional>
#include "Reader.h" 
#include "TerritoryData.h" 
#include "HierarchyIterator.h"
#include "libds/amt/implicit_sequence.h"


class ConsoleApp {


private:
	bool end_;
	TerritoryData* td_;
	HierarchyIterator* it_ = nullptr;
	bool isAlsoHierarchy_ = false;
	Block* endIt_ = nullptr; // posledny block pri prehladavani nevymazovat 

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
							startWithStrPredicate(td_->getRegions().begin(), td_->getRegions().end(), chooseOption2);
							td_->printSorted();
							startWithStrPredicate(td_->getSoorps().begin(), td_->getSoorps().end(), chooseOption2);
							td_->printSorted();
							startWithStrPredicate(td_->getVillages().begin(), td_->getVillages().end(), chooseOption2);
							td_->printSorted();
						}


						else if (chooseOption == "2") {
							startWithStrPredicate(td_->getRegions().begin(), td_->getRegions().end(), chooseOption2);
						}

						else if (chooseOption == "3") {
							startWithStrPredicate(td_->getSoorps().begin(), td_->getSoorps().end(), chooseOption2);
						}

						else if (chooseOption == "4") {
							startWithStrPredicate(td_->getVillages().begin(), td_->getVillages().end(), chooseOption2);
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
							containStrPredicate(td_->getRegions().begin(), td_->getRegions().end(), chooseOption2);
							td_->printSorted();
							containStrPredicate(td_->getSoorps().begin(), td_->getSoorps().end(), chooseOption2);
							td_->printSorted();
							containStrPredicate(td_->getVillages().begin(), td_->getVillages().end(), chooseOption2);
							td_->printSorted();

						}

						else if (chooseOption == "2") {
							containStrPredicate(td_->getRegions().begin(), td_->getRegions().end(), chooseOption2);
						}

						else if (chooseOption == "3") {
							containStrPredicate(td_->getSoorps().begin(), td_->getSoorps().end(), chooseOption2);
						}

						else if (chooseOption == "4") {
							containStrPredicate(td_->getVillages().begin(), td_->getVillages().end(), chooseOption2);
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
				<< "- Input 4. Write information about actual node\n"
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
				predicates(it_);
			}
			else if (chooseOption == "4")
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

	void predicates(HierarchyIterator* it) {
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
				processPreOrderPredicate(it->getPointerBlock(), 1, chooseOption2, true);
				td_->printSorted();
				td_->clearSortedData();
			}
			else if (chooseOption == "2") {
				std::string chooseOption2 = "  ";
				std::cout << "Input containnig characters: ";
				std::cin >> chooseOption2;
				processPreOrderPredicate(it->getPointerBlock(), 2, chooseOption2, true);
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
						break;
					}
					processPreOrderPredicate(it->getPointerBlock(), 3, type, true);
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

	ConsoleApp()
	{

	}

	~ConsoleApp()
	{
		delete td_;
		if (it_ != nullptr) {
			delete it_;
		}

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
	void processPreOrderPredicate(Block* node, int predicate, std::string param, bool first) {

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
					processPreOrderPredicate(son, predicate, param, false);
					++sonsprocessed;
				}
				++n;
			}

			if (first) {
				It end(hierarchy2, endIt_);
				if (predicate == 1) {
					startWithStrPredicate(begin, end, param);
				}
				else if (predicate == 2) {
					containStrPredicate(begin, end, param);
				}
				else {
					hasTypePredicate(begin, end, param);
				}
			}

		}
	}


	//Predikaty
	template<typename Iterator2>
	void startWithStrPredicate(Iterator2 begin, Iterator2 end, std::string param) {
		auto startsWithPr = [param](TerritorialUnit* unit) {
			return unit->getName().substr(0, param.length()) == param;
			};
		td_->find(begin, end, startsWithPr);

	}

	template<typename Iterator2>
	void containStrPredicate(Iterator2 begin, Iterator2 end, std::string param) {

		auto containsStr = [param](TerritorialUnit* unit) {
			return unit->getName().find(param) != std::string::npos;
			};

		td_->find(begin, end, containsStr);


	}

	template<typename Iterator2>
	void hasTypePredicate(Iterator2 begin, Iterator2 end, std::string param) {

		auto hasType = [param](TerritorialUnit* unit) {
			return unit->getTeritoryType() == param;
			};


		td_->find(begin, end, hasType);

	}

};
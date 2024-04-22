#pragma once
#include <string>
#include <functional>
#include "Reader.h" 
#include "TerritoryData.h" 
#include <libds/heap_monitor.h>
#include "HierarchyIterator.h"


class ConsoleApp {

private:
	bool end_;
	TerritoryData* td_;
	HierarchyIterator* it_;
	bool isAlsoHierarchy_ = false;

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

						auto startsWithPr = [chooseOption2](TerritorialUnit* unit) {
							return (unit)->getName().substr(0, chooseOption2.length()) == chooseOption2;
							};
						if (chooseOption == "1")
							td_->findInAllCategories(startsWithPr);
						else if (chooseOption == "2")
							td_->findRegions(startsWithPr);
						else if (chooseOption == "3")
							td_->findSoorps(startsWithPr);
						else if (chooseOption == "4")
							td_->findVillages(startsWithPr);

						td_->printSorted();
					}

					else if (chooseOption2 == "2") {
						std::cout << "Input pattern: ";
						std::cin >> chooseOption2;
						auto containsStr = [chooseOption2](TerritorialUnit* unit) {
							return unit->getName().find(chooseOption2) != std::string::npos;
							};

						if (chooseOption == "1")
							td_->findInAllCategories(containsStr);
						else if (chooseOption == "2")
							td_->findRegions(containsStr);
						else if (chooseOption == "3")
							td_->findSoorps(containsStr);
						else if (chooseOption == "4")
							td_->findVillages(containsStr);

						td_->printSorted();
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

	void hierarchy() {
		std::string chooseOption = "LOPASK";
		it_ = new HierarchyIterator(*td_->getHierarchy().accessRoot());
		std::cout << "Your actual node is:";
		std::cout << it_->getPointerBlock()->data_->getName() << "\n";
		while (true) {
			std::cout << "\n- Input 1 If You Want Go to Previous\n"
				<< "- Input 2 Go down\n"
				<< "- Input 3 Search By Predicate\n"
				<< "- Input 4 Write Information about actual node\n"
				<< "- Input ~ To end application\n" << 
				"Choice:";
			std::cin >> chooseOption;
			if (chooseOption == "1")
			{
				it_->goPrevious();
			}
			else if (chooseOption == "2")
			{
				while (true) {
					int i = 1;

				}
			}
			else if (chooseOption == "3")
			{
				
			}
			else if (chooseOption == "4")
			{

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

public:

	ConsoleApp()
	{
	}

	~ConsoleApp()
	{
		delete td_;
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
			else if (chooseOption == "~") {
				end_ = true;
				break;
			}
			else {
				std::cout << "- Selected wrong option !!!\n\n";
			}
		}
		std::cout << "- Application ended sucessfuly\n";
	}




};
#pragma once
#include <string>
#include <functional>
#include "Reader.h" 
#include "TerritoryData.h" 



class ConsoleApp {

private:
	bool end_;
	TerritoryData* td_;

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
						auto startsWithPr = [chooseOption2](const std::string& name) {
							return name.substr(0, chooseOption2.length()) == chooseOption2;
							};

						if (chooseOption == "1")
							td_->findAllByName(startsWithPr);
						else if (chooseOption == "2")
							td_->findRegionsByName(startsWithPr);
						else if (chooseOption == "3")
							td_->findSoorpsByName(startsWithPr);
						else if (chooseOption == "4")
							td_->findVillagesByName(startsWithPr);

						td_->printSorted();
					}

					else if (chooseOption2 == "2") {
						std::cout << "Input pattern: ";
						std::cin >> chooseOption2;
						auto containsStr = [chooseOption2](const std::string& name) {
							return name.find(chooseOption2) != std::string::npos;
							};

						if (chooseOption == "1")
							td_->findAllByName(containsStr);
						else if (chooseOption == "2")
							td_->findRegionsByName(containsStr);
						else if (chooseOption == "3")
							td_->findSoorpsByName(containsStr);
						else if (chooseOption == "4")
							td_->findVillagesByName(containsStr);

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

			std::cout << "\n- Input 1 if you want write all Territories\n" <<
				"- Input 2 write only Regions\n" <<
				"- Input 3 write only SOORP\n" <<
				"- Input 4 write only Villages\n" <<
				"- Input 5 Search Territory by predicate\n" <<
				"- Input ~ if you want end application\n" <<
				"Choice: ";
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

public:

	ConsoleApp()
	{
	}

	~ConsoleApp()
	{
		delete td_;
	}

	void runApp() {
		State s("�esk� republika", "124a");
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

			std::cout << "- Input 1 if you want read Territorial Units from default file\n" <<
				"- Input 2 if you want read your own file\n" <<
				"- Input ~ if you want end application\n" <<
				"Choice: ";
			std::cin >> chooseOption;
			if (chooseOption == "1") {
				r->loadAllTerritoryData(path, td_);
				std::cout << "- Territories sucessfuly loaded\n";
				baseOptions();
			}
			else if (chooseOption == "2") {
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
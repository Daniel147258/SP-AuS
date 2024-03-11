#pragma once
#include <string>
#include <functional>
#include "TerritoryData.h"
#include <iostream>
#include <fstream>
#include <sstream>

class Reader {

public:

	Reader()
	{
	}

	// Pointer t zanikne v r�mci met�dy
	void loadAllTerritoryData(const std::string& nameOfFile, TerritoryData* t) {

		std::ifstream file(nameOfFile);
        
		if (!file.is_open()) {
			std::cerr << "Failed to open file: " << nameOfFile << std::endl;
		}
 
        State state("�esk� republika", "120AH");
        std::string line;
        int counter = 0;
        std::string regionName;
        std::string lastNameOfSoorp = " ";
        Region* regionPtr = nullptr;
        SOORP* soorpPtr = nullptr;
        int numberLine = 0;
        std::string regionCode, soorpCode, nameOfSoorp,
            number, villageName, villageCode, villageType,
            partsOfVillage, numberCadastre, cadastreArea, numberOfPeople, people14, people65,
            canalization, waterSupply, gass;

        while (std::getline(file, line)) {
            ++numberLine;
            std::istringstream iss(line);
            std::getline(iss, regionCode, ';');
            std::getline(iss, soorpCode, ';');
            std::getline(iss, nameOfSoorp, ';');
            std::getline(iss, number, ';');
            std::getline(iss, villageName, ';');
            std::getline(iss, villageCode, ';');
            std::getline(iss, villageType, ';');
            std::getline(iss, partsOfVillage, ';');
            std::getline(iss, numberCadastre, ';');
            std::getline(iss, cadastreArea, ';');
            std::getline(iss, numberOfPeople, ';');
            std::getline(iss, people14, ';');
            std::getline(iss, people65, ';');
            std::getline(iss, canalization, ';');
            std::getline(iss, waterSupply, ';');
            std::getline(iss, gass, ';');


            // Osetrenie Kanalizacie a atd.. 
            try {
               std::stoi(canalization);
            }
            catch (const std::invalid_argument&) {
                canalization = "0";
            }
            catch (const std::out_of_range&) {
                canalization = "0";
            }

            try {
               std::stoi(waterSupply);
            }
            catch (const std::invalid_argument&) {
                waterSupply = "0";
            }
            catch (const std::out_of_range&) {
                waterSupply = "0";
            }

            try {
                std::stoi(gass);
            }
            catch (const std::invalid_argument&) {
                gass = "0";
            }
            catch (const std::out_of_range&) {
                gass = "0";
            }

            if (counter > 0) {
                regionPtr = new Region(regionName, regionCode, state);
                t->addRegion(regionPtr);
                counter = 0;
            }

            if (regionCode.empty() && soorpCode.empty()) {
                regionName = nameOfSoorp;
                ++counter;
            }

            if (nameOfSoorp != lastNameOfSoorp && counter < 1 && regionPtr != nullptr) {
                Region& region = *regionPtr;
                soorpPtr = new SOORP(nameOfSoorp, soorpCode, region);
                lastNameOfSoorp = nameOfSoorp;
                t->addSOORP(soorpPtr);
            }
            if (soorpPtr != nullptr && !villageName.empty() && !villageCode.empty()) {
                try {
                    int partsOfVillageInt = std::stoi(partsOfVillage);
                    int numberCadastreInt = std::stoi(numberCadastre);
                    int cadastreAreaInt = std::stoi(cadastreArea);
                    int numberOfPeopleInt = std::stoi(numberOfPeople);
                    int people14Int = std::stoi(people14);
                    int people65Int = std::stoi(people65);
                    int canalizationInt = std::stoi(canalization);
                    int waterSupplyInt = std::stoi(waterSupply);
                    int gassInt = std::stoi(gass);

                    SOORP& soorp = *soorpPtr;
                    t->addVillage(new Village(villageName, villageCode, soorp, villageType, partsOfVillageInt, numberCadastreInt, cadastreAreaInt, numberOfPeopleInt,
                        people14Int, people65Int, canalizationInt, waterSupplyInt, gassInt));
                }
                catch (const std::invalid_argument& e) {
                    
                    std::cerr << "Error: Village have wrong parameter(Expected number) at line: " << numberLine << " " << e.what() << std::endl;
                }
                catch (const std::out_of_range& e) {
                    std::cerr << "Error: Number is out of range in integer:  at line: " << numberLine << " " << e.what() << std::endl;
                }
                
            }
			
        }
        file.close();
	}


};

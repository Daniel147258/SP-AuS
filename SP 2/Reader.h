#pragma once
#include <string>
#include <functional>
#include "TerritoryData.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

class Reader {

public:

    Reader()
    {
    }

    ~Reader() {}

    // Odstrani medezeri v stringu potrebne na prevod cisiel cez std::stoi
    void removeSpaces(std::string& str) {
        str.erase(std::remove_if(str.begin(), str.end(), [](unsigned char c) { return std::isspace(c); }), str.end());
    }

    // Pointer t zanikne v rámci metódy
    bool loadAllTerritoryData(const std::string& nameOfFile, TerritoryData* t) {

        std::ifstream file(nameOfFile);

        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << nameOfFile << std::endl;
            return false;
        }
        // odstranenie hlavicky v suboru ktora predstavuje 3 bajty 
        file.ignore(3);
        TerritorialUnit* state = new State("Èeská republika", "120AH");
        std::string line;
        int counter = 0;
        std::string regionName;
        std::string lastNameOfSoorp = " ";
        TerritorialUnit* regionPtr = nullptr;
        TerritorialUnit* soorpPtr = nullptr;
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

            removeSpaces(partsOfVillage);
            removeSpaces(numberCadastre);
            removeSpaces(cadastreArea);
            removeSpaces(numberOfPeople);
            removeSpaces(people14);
            removeSpaces(people65);
            removeSpaces(canalization);
            removeSpaces(waterSupply);
            removeSpaces(gass);

            // Osetrenie Kanalizacie a ...atd kvoli znakom ako su "-" ...atd
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
                t->addRegion(dynamic_cast<Region*>(regionPtr));
                counter = 0;
            }

            if (regionCode.empty() && soorpCode.empty()) {
                regionName = nameOfSoorp;
                ++counter;
            }

            if (nameOfSoorp != lastNameOfSoorp && counter < 1 && regionPtr != nullptr) {
                soorpPtr = new SOORP(nameOfSoorp, soorpCode, regionPtr);
                lastNameOfSoorp = nameOfSoorp;
                t->addSOORP(dynamic_cast<SOORP*>(soorpPtr));
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

                    t->addVillage(new Village(villageName, villageCode, soorpPtr, villageType, partsOfVillageInt, numberCadastreInt, cadastreAreaInt, numberOfPeopleInt,
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
        return true;
    }


    // nacita data ja do hierarchie
    bool loadAllTerritoryDataToHierarchy(const std::string& nameOfFile, TerritoryData* t) {

        std::ifstream file(nameOfFile);

        if (!file.is_open()) {
            std::cerr << "Failed to open file: " << nameOfFile << std::endl;
            return false;
        }
        // odstranenie hlavicky v suboru ktora predstavuje 3 bajty 
        file.ignore(3);
        // Stat
        TerritorialUnit* state = &t->getState();
        Block* stateBlock = new Block();
        stateBlock->parent_ = nullptr;
        stateBlock->data_ = &t->getState();
        t->getHierarchy().changeRoot(stateBlock);
        Block* regionBlock = nullptr;
        Block* soorpBlock = nullptr;
        Block* villageBlock = nullptr;
        std::string line;
        int counter = 0;
        std::string regionName;
        std::string lastNameOfSoorp = " ";
        TerritorialUnit* regionPtr = nullptr;
        TerritorialUnit* soorpPtr = nullptr;
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

            removeSpaces(partsOfVillage);
            removeSpaces(numberCadastre);
            removeSpaces(cadastreArea);
            removeSpaces(numberOfPeople);
            removeSpaces(people14);
            removeSpaces(people65);
            removeSpaces(canalization);
            removeSpaces(waterSupply);
            removeSpaces(gass);

            // Osetrenie Kanalizacie a ...atd kvoli znakom ako su "-" ...atd
            try {
                int a = std::stoi(canalization);
            }
            catch (const std::invalid_argument&) {
                canalization = "0";
            }
            catch (const std::out_of_range&) {
                canalization = "0";
            }

            try {
                int b = std::stoi(waterSupply);
            }
            catch (const std::invalid_argument&) {
                waterSupply = "0";
            }
            catch (const std::out_of_range&) {
                waterSupply = "0";
            }

            try {
               int c = std::stoi(gass);
            }
            catch (const std::invalid_argument&) {
                gass = "0";
            }
            catch (const std::out_of_range&) {
                gass = "0";
            }

            if (counter > 0) {
                regionPtr = new Region(regionName, regionCode, state);
                regionBlock = new Block();
                regionBlock->parent_ = stateBlock;
                regionBlock->data_ = regionPtr;
                t->addRegion(dynamic_cast<Region*>(regionPtr));
                t->addSon(stateBlock, regionBlock);
                counter = 0;
            }

            if (regionCode.empty() && soorpCode.empty()) {
                regionName = nameOfSoorp;
                ++counter;
            }

            if (nameOfSoorp != lastNameOfSoorp && counter < 1 && regionPtr != nullptr) {
                soorpPtr = new SOORP(nameOfSoorp, soorpCode, regionPtr);
                lastNameOfSoorp = nameOfSoorp;
                soorpBlock = new Block();
                soorpBlock->parent_ = regionBlock;
                soorpBlock->data_ = soorpPtr;
                t->addSOORP(dynamic_cast<SOORP*>(soorpPtr));
                t->addSon(regionBlock,soorpBlock);
              
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

                    TerritorialUnit* villagePtr = new Village(villageName, villageCode, soorpPtr, villageType, partsOfVillageInt, numberCadastreInt, cadastreAreaInt, numberOfPeopleInt,
                        people14Int, people65Int, canalizationInt, waterSupplyInt, gassInt);

                    villageBlock = new Block();
                    villageBlock->parent_ = soorpBlock;
                    villageBlock->data_ = villagePtr;
                    t->addVillage(dynamic_cast<Village*>(villagePtr));
                    t->addSon(soorpBlock, villageBlock);
                   

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
        return true;
    }


};

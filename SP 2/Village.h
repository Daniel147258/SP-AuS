#pragma once
#include <string>
#include <functional>
#include "TerritorialUnit.h"
#include "SOORP.h"
#include <Windows.h>
#include <libds/heap_monitor.h>

class Village : public TerritorialUnit {

private:

	TerritorialUnit* soorp_;
	std::string villageType_;
	const std::string territoryType_ = "Village";
	int countPartsOfVillage_;
	int numberOfCadastre_;
	int cadastreArea_;
	int numberOfPeople_;
	int numberOfPeopleTo14_;
	int numberOfPeopleUp65_;
	int numberOfPeopleFrom15To64_;
	int canalization_;
	int waterSupply_;
	int gass_;

public:

	Village(std::string& name, std::string& code, TerritorialUnit* soorp, std::string& villageType, int& countPartsOfVillage,
		int& numberOfCadastre, int& cadastreArea, int& numberOfPeople, int& numberOfPeopleTo14, int& numberOfPeopleUp65,
		int& canalization, int& waterSupply, int& gass)
		: TerritorialUnit(name, code), soorp_(soorp), villageType_(villageType), countPartsOfVillage_(countPartsOfVillage),
		numberOfCadastre_(numberOfCadastre), cadastreArea_(cadastreArea), numberOfPeople_(numberOfPeople),
		numberOfPeopleTo14_(numberOfPeopleTo14), numberOfPeopleUp65_(numberOfPeopleUp65), canalization_(canalization), waterSupply_(waterSupply), gass_(gass)
	{
		Village::setNumberOfPeopleFrom15To64_();

	}



	TerritorialUnit& getPrevious() override
	{
		return *soorp_;
	}

	const std::string& getTeritoryType() override
	{
		return territoryType_;
	}

	std::string& getVillageType()
	{
		return villageType_;
	}

	void setNumberOfPeopleFrom15To64_()
	{
		numberOfPeopleFrom15To64_ = numberOfPeople_ - numberOfPeopleTo14_ - numberOfPeopleUp65_;
	}

	int getCountPartsOfVillage() const { return countPartsOfVillage_; }
	int getNumberOfCadastre() const { return numberOfCadastre_; }
	int getNumberOfPeople() const { return numberOfPeople_; }
	int getNumberOfPeopleTo14() const { return numberOfPeopleTo14_; }
	int getNumberOfPeopleUp65() const { return numberOfPeopleUp65_; }
	int getNumberOfPeopleFrom15To64() const { return numberOfPeopleFrom15To64_; }


	std::string toString() override {
		return
			"Name: " + getName() +
			"\nCode: " + getCode() +
			"\nType: " + getTeritoryType() +
			"\nPopulation: " + std::to_string(getNumberOfPeople()) +
			"\nPopulation to 14 years: " + std::to_string(getNumberOfPeopleTo14()) +
			"\nPopulation from 15 to 64 years: " + std::to_string(getNumberOfPeopleFrom15To64()) +
			"\nPopulaton from 65 years: " + std::to_string(getNumberOfPeopleUp65()) +
			"\nSOORP: " + getPrevious().getName() +
			"\nVillage parts: " + std::to_string(getCountPartsOfVillage()) +
			"\nCadastre: " + std::to_string(getNumberOfCadastre()) +
			"\nCanalization: " + getCanalization() +
			"\nWater supply: " + getWaterSupply() +
			"\nGass: " + getGass();
	}

	std::string getCanalization() const
	{

		if (canalization_ == 2) {
			return "Have canalization with connection on èov";
		}
		else if (canalization_ == 1)
		{
			return "Have canalization without connection on èov";
		}
		else if (canalization_ == 0)
		{
			return "Don't have canalization";
		}
		else {
			return "No data about canalization";
		}

	}

	std::string getWaterSupply() const
	{

		if (waterSupply_ == 2) {
			return "Have water supply with connection on èov";
		}
		else if (waterSupply_ == 1)
		{
			return "Have water supply without connection on èov";
		}
		else if (waterSupply_ == 0)
		{
			return "Don't have water supply";
		}
		else {
			return "No data about water supply";
		}

	}

	std::string getGass() const
	{

		if (gass_ == 2) {
			return "Have gass with connection on èov";
		}
		else if (gass_ == 1)
		{
			return "Have gass without connection on èov";
		}
		else if (gass_ == 0)
		{
			return "Don't have gass";
		}
		else {
			return "No data about gass";
		}

	}
};
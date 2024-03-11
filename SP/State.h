#pragma once
#include <string>
#include <functional>
#include "TerritorialUnit.h"

class State : public TerritorialUnit {

private:

	const std::string territoryType_ = "State";

public:

	State(std::string& name, std::string& code)
		: TerritorialUnit(name, code)
	{

	}

	State(std::string name, std::string code)
		: TerritorialUnit(name, code)
	{

	}

	TerritorialUnit& getPrevious() override {
		throw std::runtime_error("No previous Territorial units available");
	}


	const std::string& getTeritoryType() override {
		return territoryType_;
	}
};
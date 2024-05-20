#pragma once
#include <string>
#include <functional>
#include "TerritorialUnit.h"
#include <stdexcept>


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

	~State() {

	}

	TerritorialUnit& getPrevious() override {
		throw std::runtime_error("No previous Territorial units available");
	}

	std::string toString() override {
		return "- Name: " + getName() + "\n- Code: " + getCode() + "\n- Type: " + territoryType_ + "\n";
	}
	const std::string& getTeritoryType() override {
		return territoryType_;
	}
};
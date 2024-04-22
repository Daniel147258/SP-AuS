#pragma once
#include <string>
#include <functional>
#include "TerritorialUnit.h"
#include "State.h"
#include <libds/heap_monitor.h>

class Region : public TerritorialUnit {

private:

	TerritorialUnit* state_;
	const std::string territoryType_ = "Region";

public:


	Region(std::string& name, std::string& code, TerritorialUnit* state)
		: TerritorialUnit(name, code), state_(state)
	{
	}

	TerritorialUnit& getPrevious() override {
		return *state_;
	}

	const std::string& getTeritoryType() override {
		return territoryType_;
	}

	std::string toString() override {
		return "- Name: " + getName() + "\n- Code: " + getCode() + "\n- Type: " + territoryType_ + "\n";
	}
};
#pragma once
#include <string>
#include <functional>
#include "TerritorialUnit.h"
#include "Region.h"
#include <libds/heap_monitor.h>

class SOORP : public TerritorialUnit {

private:

	TerritorialUnit* region_;
	const std::string territoryType_ = "SOORP";

public:

	SOORP(std::string& name, std::string& code, TerritorialUnit* region)
		: TerritorialUnit(name, code), region_(region)
	{
	}

	TerritorialUnit& getPrevious() override
	{
		return *region_;
	}

	const std::string& getTeritoryType() override {
		return territoryType_;
	}

	std::string toString() override {
		return "- Name: " + getName() + "\n- Code: " + getCode() + "\n- Type: " + territoryType_ + "\n";
	}
};

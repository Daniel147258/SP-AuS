#pragma once
#include <string>
#include <functional>
#include "TerritorialUnit.h"
#include "Region.h"

class SOORP : public TerritorialUnit {

private:

	Region& region_;
	const std::string territoryType_ = "SOORP";

public:

	SOORP( std::string& name,  std::string& code, Region& region)
		: TerritorialUnit(name, code), region_(region)
	{

	}

	TerritorialUnit& getPrevious() override 
	{
		return region_;
	}

	const std::string& getTeritoryType() override {
		return territoryType_;
	}
};

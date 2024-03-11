#pragma once
#include <string>
#include <functional>



class TerritorialUnit {

private:

	std::string name_;
	std::string code_;

public:
	
	TerritorialUnit(std::string& name, std::string& code)
		: name_(name), code_(code) 
	{

	}

	TerritorialUnit(const char* name, const char* code)
		: name_(name), code_(code) 
	{

	}

	const std::string& getName() const 
	{
		return name_;
	}

	const std::string& getCode() const
	{
		return code_;
	}

	virtual TerritorialUnit& getPrevious() = 0;
	virtual const std::string& getTeritoryType() = 0;
};
	
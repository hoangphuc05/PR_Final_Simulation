#pragma once

#include <string>
#include "Record.h"

class Resident {
private:
	std::string name;

public:
	Resident(std::string name): name(name) {}
	//return the name of the resident
	std::string getName() {
		return name;
	}
};
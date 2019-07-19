#pragma once

#include <string>
#include "Record.h"

class Resident {
private:
	std::string name;
	
	

public:
	Resident(std::string name): name(name) {}
	

	std::string getName() {
		return name;
	}

	

};
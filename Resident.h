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

	//just for testing
	void print() {
		std::cout << name << std::endl;
	}

};
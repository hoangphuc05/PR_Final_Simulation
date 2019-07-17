#pragma once

#include <string>
#include "Record.h"

class Resident {
private:
	std::string name;
	Record *file;
	

public:
	Resident(std::string name): name(name) {
		file = NULL;
	}

	bool addRecord(Record *inFile) {
		if (file == NULL) {
			file = inFile;
			return true;
		}
		else
			return false;
		
	}
	Record* getRecord() {
		
		return file;
	}

	void visit(int priority) {
		file->visit(priority);
	}

	std::string getName() {
		return name;
	}

	//just for testing
	void print() {
		std::cout << name << std::endl;
	}

};
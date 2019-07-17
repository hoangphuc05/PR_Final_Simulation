#pragma once

#include <vector>
#include <map>

class Record {
private:
	int numberOfVisit;
	std::vector<int> servereList;

public:
	Record() {
		numberOfVisit = 0;
	};
	Record(int servere) {
		numberOfVisit = 1;
		servereList.push_back(servere);
		
	}
	void visit(int servere) {
		numberOfVisit++;
		servereList.push_back(servere);
	}

	int at(int index) {
		if (index < numberOfVisit && index > -1)
			return servereList[index];
		else
			return -1;
	}

	int operator [] (int index) {
		return at(index);
	}

	std::map<int, int> listAll() {
		std::map<int, int> allRec;
		for (int i = 0; i < numberOfVisit; i++) {
			allRec[i] = servereList[i];
		}
		return allRec;

	}
	

};
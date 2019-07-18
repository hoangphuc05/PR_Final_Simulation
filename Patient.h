#pragma once
#include <string>
#include "Resident.h"
#include "Random.h"


extern Random myRandom;//Global variable

class Patient {
private:
	Resident *person;

	int treatTime;
	int priority;
	int begin_time;//time when resident start to become patient

public:
	Patient(Resident* owner, Record * inFile, int time) {
		treatTime = -1;
		person = owner;
		//create priority
		int prob = myRandom.next_int(100);
		if (prob < 10)
			priority = myRandom.inRange(16, 20);
		else if (prob < 30)
			priority = myRandom.inRange(11, 15);
		else
			priority = myRandom.inRange(1, 10);
		begin_time = time;
		//person->addRecord(inFile);
		//person->visit(priority);
		std::cout << owner->getName() << " is sicked with priority: " << priority << std::endl;
	}
	Resident *getResident() {
		return person;
	}
	std::string getName() {
		return person->getName();
	}
	int getBeginTime() {
		return begin_time;
	}
	int getTreatTime() {
		return treatTime;
	}
	int getPriority() {
		return priority;
	}
	void setTreatTime(int time) {
		treatTime = time;

	}
	bool operator < (Patient& another) {
		if (this->priority < another.priority)
			return true;
		else if (this->priority == another.priority) {
			if (this->getName() < another.getName()) {
				return true;
			}
		}
		else
			return false;
	}

	//Record *getRecord() {
		//return person->getRecord();
	//}
};

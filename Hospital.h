#pragma once
#include <map>
#include <string>
#include "Record.h"
#include "CareGivers.h"
#include <queue>
#include "Patient.h"
#include "Resident.h"

class Hospital {
private:
	std::map<std::string, Record*> hospitalFile;
	std::vector<CareGivers *> personnel;
	std::priority_queue<Patient *> patients;

public:
	Hospital() {}

	void addPersonnel(CareGivers* newPerson) {
		personnel.push_back(newPerson);
	}
	
	//receive a resident->become a patient
	void addPatient(Resident* newSick) {

		//check if the resident have an existing file in the hospital
		if (hospitalFile.find(newSick->getName()) == hospitalFile.end()) {
			//not found
			//create a file associate with that person
			hospitalFile[newSick->getName()] = new Record;
		}
		else {
			//found
			//do nothing?
		}

		//person become a patient, push to the priority queue
		patients.push(new Patient(newSick, hospitalFile[newSick->getName()]));

	}



};
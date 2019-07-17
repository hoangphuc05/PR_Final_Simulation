#pragma once
#include <map>
#include <iostream>
#include <typeinfo>
#include <string>
#include "Record.h"
#include "CareGivers.h"
#include <queue>
#include "Patient.h"
#include "Resident.h"
#include "Doctor.h"
#include "Nurse.h"
#include "Village.h"

extern Random myRandom;

class Hospital {
private:
	int arrival_rate, doctors_count, nurse_count;
	int runTime;
	std::map<std::string, Record*> hospitalFile;
	std::vector<CareGivers *> personnel;
	std::priority_queue<Patient *> patients;

public:
	Hospital() {
		runTime = 10080;//minutes
	}

	void addPersonnel(CareGivers* newPerson) {
		personnel.push_back(newPerson);
	}
	
	//receive a resident->become a patient
	void addPatient(Resident* newSick, int clock) {

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
		patients.push(new Patient(newSick, hospitalFile[newSick->getName()], clock));

	}
	void input_data() {
		std::cout << "Arrival rate (patient/hour): ";
		int rate;
		std::cin >> rate;
		arrival_rate = rate / 60;
		std::cout << "Number of doctors: ";
		std::cin >> doctors_count;
		std::cout << "Number of Nurses: ";
		std::cin >> nurse_count;

		for (int i = 0; i < doctors_count; i++)
			addPersonnel(new Doctor);
		for (int i = 0; i < nurse_count; i++)
			addPersonnel(new Nurse);
	}

	bool startTreatment(Patient* inPatient) {
		//patient pointer will be in the doctor/nurse object
		if (inPatient->getPriority() > 10) {
			//loop through the vector and search for doctor
			for (int i = 0; i < personnel.size(); i++) {
				if (typeid(Doctor) == typeid(*personnel[i])) {
					//check if the doctor is free?
					if (personnel[i]->isFree()) {
						personnel[i]->receivePatient(inPatient);
						return true;
					}
				}
			}
		}
		else {//both doctor and nurse can treat, prior to nurse
			//loop through the vector and search for nurse
			for (int i = 0; i < personnel.size(); i++) {
				if (typeid(Nurse) == typeid(*personnel[i])) {
					//check if the doctor is free?
					if (personnel[i]->isFree()) {
						personnel[i]->receivePatient(inPatient);
						return true;
					}
				}
			}
			//no nurse available, search for doctor
			for (int i = 0; i < personnel.size(); i++) {
				if (typeid(Doctor) == typeid(*personnel[i])) {
					//check if the doctor is free?
					if (personnel[i]->isFree()) {
						personnel[i]->receivePatient(inPatient);
						return true;
					}
				}
			}
		}
		//no available caregivers capable of the patient/no caregivers at all
		return false;
	}

	void run() {
		Village village273;
		//for debugging
		std::cout << "Hospital started!\n";
		//for loop to run a week
		for (int clock = 0; clock < runTime; clock++) {
			if (myRandom.next_double() < arrival_rate) {
				//add a patient by the rate, record the arrival time
				addPatient(village273.getSick(), clock);
			}
			//get the patient in the priority queue, see if any doctor/nurse can treat
			Patient* topPatient = patients.top();
			if (startTreatment(patients.top())) {
				patients.pop();
			}

		}

		
	}



};
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
	int runTime, doctors_count, nurse_count, total_patient;
	double arrival_rate;
	int total_time;
	std::map<std::string, Record*> hospitalFile;
	std::vector<CareGivers *> personnel;//all the doctor/nurse
	std::priority_queue<Patient *> lowPatients;
	std::priority_queue<Patient *> highPatients;

public:
	Hospital() {
		runTime = 10080;//minutes = 1 week
		total_time = 0;
		total_patient = 0;
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
			//do nothing
		}

		//person become a patient, push to the priority queue
		//create a new patient
		Patient *newIn = new Patient(newSick, hospitalFile[newSick->getName()], clock);
		//add a visit to the pation/resident record
		hospitalFile[newIn->getName()]->visit(newIn->getPriority());

		if (newIn->getPriority() < 11) {
			lowPatients.push(newIn);
		}
		else {
			highPatients.push(newIn);
		}


	}
	void input_data() {
		std::cout << "Arrival rate (patient/hour): ";
		double rate;
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
	//for plotting purpose
	
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
		//prompt user for input data: arrival rate, number of doctors and nurses
		input_data();

		std::cout << "Hospital started!\n";
		//for loop to run a week
		for (int clock = 0; clock < runTime; clock++) {
			if (myRandom.next_double() < arrival_rate && village273.peopleLeft()) {
				//add a patient by the rate, record the arrival time
				Resident *incomming = village273.getSick();
				addPatient(incomming, clock);
			}

			//check all the doctors/nurse to see if they finished with their patient
			for (int i = 0; i < personnel.size(); i++) {
				if (personnel[i]->isFinished()) {
					//if they finish: get the arrival time and caculate the time they were in, add it to total time
					total_patient++;
					total_time += clock - personnel[i]->getPatient()->getBeginTime();
					//add the patient back to the village as a normal person
					village273.backHome(personnel[i]->getPatient()->getResident());
					//the patient finished, get deleted
					personnel[i]->releasePatient();
				}
			}
			if (!highPatients.empty()) {//check for 11-20 patient
				//get the patient in the priority queue, see if any doctor/nurse can treat
				if (startTreatment(highPatients.top())) {
					highPatients.pop();//if return true, remove the patient from the queue
				}
			}
			if (!lowPatients.empty()) {//check for 1-10
				if (startTreatment(lowPatients.top())) {
					lowPatients.pop();
				}
			}

			//update the treatment time for all the personnel
			for (int i = 0; i < personnel.size(); i++) {
				personnel[i]->updateTime();
			}

			//std::cout << std::endl;
		}
		std::cout << "Average visit time of patient: " << total_time / total_patient << std::endl;
		//std::cout << "Number of files created: " << hospitalFile.size() << std::endl;
		
		
	}

	void listAllName() {
		std::cout << "All name of treated resident: \n";
		int count = 0;
		for (std::map<std::string, Record*>::iterator it = hospitalFile.begin(); it != hospitalFile.end(); it++) {
			std::cout << it->first;
			if (count == 5) {
				std::cout << std::endl;
				count = 0;
			}
			else {
				count++;
				std::cout << "\t\t";
			}
		}
	}
	void printRecord() {
		std::string inName;
		std::cout << "Name of the record: ";
		std::cin >> inName;
		if (hospitalFile.find(inName) == hospitalFile.end()) {
			//not found
			//create a file associate with that person
			std::cout << "Record does not exist!\n";
		}
		else {
			//found
			for (int i = 0; i < hospitalFile[inName]->getNumber(); i++) {
				std::cout << "Visit number: " << i + 1 << " has severity of " << hospitalFile[inName]->at(i) << std::endl;
			}
		}
		
	}

};
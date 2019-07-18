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
	std::priority_queue<Patient *> patients;

public:
	Hospital() {
		runTime = 10080;//minutes
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
			//do nothing?
		}

		//person become a patient, push to the priority queue
		patients.push(new Patient(newSick, hospitalFile[newSick->getName()], clock));

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
		input_data();
		std::cout << "Hospital started!\n";
		//for loop to run a week
		for (int clock = 0; clock < runTime; clock++) {
			std::cout << "Clock: " << clock << std::endl;
			std::cout << "normal count: " << village273.coutNormal() << std::endl;
			std::cout << "Total wait: " << total_time << std::endl;
			//std::cout << "people in hospital queue: " << patients.size() << std::endl;
			//std::cout << "next random:  " << myRandom.next_double() << std::endl;
			//std::cout << "arrival rate: " << arrival_rate << std::endl;
			if (myRandom.next_double() < arrival_rate && village273.peopleLeft()) {
				//add a patient by the rate, record the arrival time
				addPatient(village273.getSick(), clock);
				total_patient++;
			}

			//check all the doctors/nurse to see if they finished with their patient
			for (int i = 0; i < personnel.size(); i++) {
				if (personnel[i]->isFinished() ) {
					//if they finish: get the arrival time and caculate the time they were in, add it to total time
					total_time += clock - personnel[i]->getPatient()->getBeginTime();
					//add the patient back to the village as a normal person
					village273.backHome(personnel[i]->getPatient()->getResident());
					//the patient finished, get deleted
					personnel[i]->releasePatient();
				}
			}
			if (!patients.empty()) {
				//get the patient in the priority queue, see if any doctor/nurse can treat
				if (startTreatment(patients.top())) {
					patients.pop();//if return true, remove the patient from the queue
				}
			}

			//update the treatment time for all the personnel
			for (int i = 0; i < personnel.size(); i++) {
				personnel[i]->updateTime();
			}

			
		}
		std::cout << "time per patient: " << total_time / total_patient << std::endl;
		
	}



};
#pragma once

#include "Patient.h"
class CareGivers {
private:
	Patient* subject;
	virtual void generateTime() = 0;
	//int timeLeft;
protected:
	int timeLeft;
	

public:
	CareGivers() {
		timeLeft = -1;
		subject = NULL;
	}
	//for receiving the patient
	void receivePatient(Patient* incoming) {
		subject = incoming;
		generateTime();
	}
	//for giving out the pointer after the treatment is finished
	Patient* getPatient() {
		return subject;
	}
	void releasePatient() {
		delete subject;//as the person will nolonger be patient, new patient will be created from resident
		subject = NULL;
	}
	//check if the nurse/doctor finished
	bool isFinished() {
		if (timeLeft == 0 && subject != NULL)
			return true;
		else
			return false;
	}

	//check if they still holding a patient object
	//This should be called before releasing the object to prevent memory leak
	bool isFree() {
		if (subject == NULL)
			return true;
		else
			return false;
	}
	
	//remain time until the doctor/nurse finish treatment
	int	getRemainTime() {
		return timeLeft;
	}
	//should be call after every minutes
	void updateTime() {
		if (timeLeft > 0)
			timeLeft--;
	}
};
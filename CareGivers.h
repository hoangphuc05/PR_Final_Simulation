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
	

	void receivePatient(Patient* incoming) {
		subject = incoming;
		generateTime();
	}
	Patient* getPatient() {
		return subject;
	}
	void releasePatient() {
		delete subject;//as the person will nolonger be patient, new patient will be created from resident
		subject = NULL;
	}
	bool isFinished() {
		if (timeLeft == 0 && subject != NULL)
			return true;
		else
			return false;
	}

	bool isFree() {
		if (subject == NULL)
			return true;
		else
			return false;
	}
	
	int	getRemainTime() {
		return timeLeft;
	}
	void updateTime() {
		if (timeLeft > 0)
			timeLeft--;
	}
};
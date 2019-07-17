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
	bool isFree() {
		if (subject == NULL)
			return true;
		else
			return false;
	}
	
	int	getRemainTime() {
		return timeLeft;
	}
	int updateTime() {
		timeLeft--;
	}
};
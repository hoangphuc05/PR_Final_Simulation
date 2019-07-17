#pragma once
#include "Patient.h"
class CareGivers {
private:
	Patient* subject;
	//int timeLeft;
protected:
	int timeLeft;

public:
	CareGivers() {
		timeLeft = -1;
		subject = NULL;
	}
	void getPatient(Patient* incoming) {
		subject = incoming;
	}
	virtual int generateTime() = 0;
	int	getRemainTime() {
		return timeLeft;
	}
	int updateTime() {
		timeLeft--;
	}
};
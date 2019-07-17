#pragma once
#include "CareGivers.h"


extern Random myRandom;
class Nurse : public CareGivers {
public:
	Nurse(): CareGivers(){}

	int generateTime() {
		timeLeft = myRandom.inRange(1, 10);
		return timeLeft;
	}
};
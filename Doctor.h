#pragma once
#include "CareGivers.h"

extern Random myRandom;
class Doctor :public CareGivers {
public:
	Doctor() : CareGivers() {}

	int generateTime() {
		timeLeft = myRandom.inRange(1, 20);
		return timeLeft;
	}
};
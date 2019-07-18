#pragma once
#include "CareGivers.h"

extern Random myRandom;
class Doctor :public CareGivers {
private:
	void generateTime() {
		timeLeft = myRandom.inRange(1, 20);
	}
public:
	Doctor() : CareGivers() {}

	
};
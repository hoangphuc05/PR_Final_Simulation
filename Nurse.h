#pragma once
#include "CareGivers.h"


extern Random myRandom;
class Nurse : public CareGivers {
private:
	void generateTime() {
		timeLeft = myRandom.inRange(1, 10);
	}
public:
	Nurse(): CareGivers(){}

	
};
//#pragma once
//taken from the airport simulator project
#ifndef RANDOM_H_
#define RANDOM_H_

#include <cstdlib>
#include <ctime>

/** Class to encapsulate the standard random number generator. */
class Random {

public:

	/** Initializes the random number generator using the time
		as the seed.
	*/
	Random() {
		srand((unsigned int)std::time(NULL));
	}

	/** Initializes the randon mumber generator using a
		supplied seed.
	*/
	Random(int seed) {
		srand(seed);
	}

	/** Returns a random integer in the range 0 – n. */
	int next_int(int n) {
		return int(next_double() * n);
	}

	int inRange(int low, int high) {
		high++;
		return next_int(high - low) + low;
	}

	/** Return a random double in the range 0 – 1. */
	double next_double() {
		return double(rand()) / RAND_MAX;
	}

};

#endif
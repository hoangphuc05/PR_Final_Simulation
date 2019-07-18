#pragma once
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include <iostream>
#include <queue>
#include "Resident.h"
#include "Random.h"
#include "Patient.h"

extern Random myRandom;

class Village {
private:

	//std::queue <Resident *> healthyVillagers;
	std::vector <Resident *> normalVillagers;

public:
	Village() {
		std::ifstream nameFile;
		nameFile.open("name.txt");
		std::string name;

		if (nameFile.is_open()) {
			while (!nameFile.eof()) {
				nameFile >> name;
				

				normalVillagers.push_back(new Resident(name));
			}
		}
		else {
			std::cout << "File is not opened, cannot read name!\n";
		}

	}

	//return a resident pointer to hospital
	Resident* getSick() {
		/*if (!healthyVillagers.empty()) {
			Resident *sicking = healthyVillagers.front();
			//std::cout << sicking->getName() << " get sick\n";
			healthyVillagers.pop();
			return sicking;
		}
		else  {
			int index = myRandom.inRange(0, normalVillagers.size() - 1);
			Resident *sicking = normalVillagers[index];
			normalVillagers.erase(normalVillagers.begin() + index);
			return sicking;
		}
		//else//all people are sick, no more in the village
			//return NULL;;*/

		if (!normalVillagers.empty()) {
			int index = myRandom.inRange(0, normalVillagers.size() - 1);
			Resident *willSick = normalVillagers[index];
			normalVillagers.erase(normalVillagers.begin() + index);
			return willSick;
		}
	}

	//get a resident back to normal
	void backHome(Resident* person) {
		//std::cout << person->getName() << " back home\n";
		normalVillagers.push_back(person);
		
	}

	bool peopleLeft() {
		if (normalVillagers.empty())
			return false;
		else
			return true;
	}

	//for debugging
	int coutNormal() {
		return normalVillagers.size();
	}


};

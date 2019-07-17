//Final project of Phuc Cai
//Hospital simulator
//inheritance, polymorphism
//set, map, hash table
//queues/priority queue

#include <iostream>
#include "Record.h"
#include <fstream>
#include <string>
#include <stdlib.h>//for srand
#include <map>
#include "Village.h"
#include "Resident.h"
#include "Random.h"
#include "Doctor.h"

using namespace std;
Random myRandom;

int main() {
	
	map<string, Record*> testMap;

	Village myVille;

	Patient sickGuy(myVille.getSick(), new Record);
	Doctor aDoc;
	cout << "a";
	aDoc.generateTime();
	cout << aDoc.getRemainTime() << endl;

	testMap["Phuc"] = new Record(3);
	testMap["Phuc"]->visit(12);
	cout << testMap["Phuc"]->at(1) << endl;
	
	
	system("pause");
}
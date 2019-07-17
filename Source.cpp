//Final project of Phuc Cai
//Hospital simulator
//inheritance, polymorphism
//set, map, hash table
//queues/priority queue

#include <iostream>
#include <queue>
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
	priority_queue<int> testIn;
	
	Doctor aDoc;
	cout << "a";
	aDoc.generateTime();
	cout << aDoc.getRemainTime() << endl;
	testIn.push(3);
	testIn.push(5);
	cout << testIn.top();
	cout << testIn.top();
	
	
	system("pause");
}
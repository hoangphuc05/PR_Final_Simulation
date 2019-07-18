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
#include "Hospital.h"
#include "ReadInt.h"

using namespace std;
Random myRandom;

int main() {
	std::cout << "Welcome to simulation" << std::endl;
	Hospital hos273;

	hos273.run();
	
	char choice;
	do {
		cout << endl;
		int select;
		string	menu_string = "Please choose an action below:\n";
		menu_string += "0 - List all the name that were treated\n";
		menu_string += "1 - Retrieve record by name\n";
		menu_string += "Enter: ";
		select = read_int(menu_string, 0, 4);

		// Perform the banking activity based on the user selection
		switch (select) {
		case 0:
			hos273.listAllName();
			break;
		case 1:
			hos273.printRecord();
			break;
		default:
			cout << "Goodbye! Thank you for visiting.\n";
			return 0;
		}

		cout << "Do you wish to perform another transaction? (y or n): ";
		cin >> choice;
	} while (choice != 'n');

	system("pause");
}
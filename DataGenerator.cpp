#pragma once

#include "Config.h"
#include "Models/User/User.h"
#include <Windows.h>

using namespace std;


class DataGenerator
{
	static vector<string> femaleNames, maleNames, countries;


	static string randomNationalID() {
		string nationalID = "";

		for (int i = 0; i < 14; i++) {
			nationalID += '0' + (rand() % 10);
		}
		return nationalID;
	}


public:
	static bool generateUser() {
		// initialize random seed
		Sleep(1000);
		srand(time(NULL)); 

		User user;

		// Get random Full Name and Gender
		int gender = rand() % 2;

		string fullName = "";

		if (gender) {
			user.gender = "Female";
			int name = rand() % femaleNames.size();
			fullName += femaleNames[name];
		}
		else {
			user.gender = "Male";
			int name = rand() % maleNames.size();
			fullName += maleNames[name];
		}

		int name = rand() % maleNames.size();
		fullName += " " + maleNames[name];

		user.fullName = fullName;
		user.nationalID = randomNationalID();
		user.password = "12345678";
		user.age = rand() % 100 + 1;

		if (rand() % 23) {
			user.country = countries[1];
			user.government = governments[rand() % 22];
		} else {
			user.country = countries[0];
			user.government = "Abroad";
		}

		if (rand() % 3) {
			user.isVaccinated = true;
			user.dosesNumber = rand() % 3;
		}
		else {
			user.isVaccinated = false;
			user.dosesNumber = 0;
		}
		
		return user.insert();
	}
};


vector<string> DataGenerator::femaleNames = { "Enas", "Doaa", "Merna", "Safaa", "Zenab", "Mai", "Salma", "Hadeer",
		"Salsabel", "Rawda", "Arwa", "Asmaa", "Assel", "Abeer", "Yasmin", "Tasbeeh", "Sarah", "Esraa", "Alaa" };

vector<string> DataGenerator::maleNames = { "Omar", "Hesham", "Mohyy", "Fady", "Osama", "Wasfy", "Zeyad", "Ahmed", "Mohamed", "Abdallah",
	"Ali", "Mahmoud", "Amr", "Ayman", "Amgd", "Anas", "Atef", "Abdelrahman", "Abdelrazak", "Hamed", "Samer", "Amar" };

vector<string> DataGenerator::countries = { "Abroad", "Egypt" };
#pragma once
#include "../../Models/User/User.h"

class UserController
{

public:
	UserController();

	void Register(string fullName, string NationalID, string password, string gender, int age, string country, string government, bool isVaccinated, int dosesNumber);
	void Login(string nationalID, string password);
	void display();
	void edit();


	/**
	 * @brief Delete specific user account
	 * @param string nationalID of the user
	 */
	void deleteAccount(string nationalID);
};


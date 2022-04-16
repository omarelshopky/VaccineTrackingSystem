#pragma once
#include "../../Models/User/User.h"

class UserController
{

public:
	UserController();

	/***	Mohyy	***/ // RegisterView
	void signup(string fullName, string NationalID, string password, string gender, int age, string country, string government, bool isVaccinated, int dosesNumber);
	

	/***	Doaa	***/ // AdminDashboardView
	void login(string nationalID, string password);


	/***	Zeyad	***/ // UserProfileView
	User display();
	void edit();


	/**
	 * @brief Delete specific user account
	 * @param string nationalID of the user
	 */
	void deleteAccount(string nationalID);
};


#pragma once
#include "../../Models/User/User.h"

class UserController
{

public:

	/***	Mohyy	***/ // RegisterView
	void signup(string fullName, string NationalID, string password, string gender, int age, string country, string government, bool isVaccinated, int dosesNumber);
	

	/**
	 * @brief make login for user that stored in database
	 * @param string nationalID of the user and string password of the user
	 * @return bool shows if the login process for user done successfully or not (true -> login be successfully, false -> login be failed )
	 */
	bool login(string nationalID, string password);


	/***	Zeyad	***/ // UserProfileView
	User display();
	void edit();


	/**
	 * @brief Delete specific user account
	 * @param string nationalID of the user
	 */
	void deleteAccount(string nationalID);
};


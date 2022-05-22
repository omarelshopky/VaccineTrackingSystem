#pragma once
#include "../../Models/User/User.h"

class UserController
{

public:
	/**
		* @brief User registration
		* @param string fullName, string NationalID, string password, string gender, int age, string country, string government, bool isVaccinated, int dosesNumber
		* @return map to display problems of registration

		*/
	map<string, string> signup(string fullName, string nationalID, string password, string gender, int age, string country, string government, bool isVaccinated, int dosesNumber);


	/**
	 * @brief make login for user that stored in database
	 * @param string nationalID of the user and string password of the user
	 * @return bool shows if the login process for user done successfully or not (true -> login be successfully, false -> login be failed )
	 */
	bool login(string nationalID, string password);


	/**
	 * @brief Gets a user informatino from database with specific national ID
	 * @param string nationalID of the user
	 * @return User corresponding to this national ID
	 */
	User display(string nationalId);


	/**
	 * @brief Edit the user information
	 * @param The User to edit his information
	 * @return a map include the state of the edit
	 */
	map<string, string> edit(User);


	/**
	 * @brief Delete specific user account
	 * @param string nationalID of the user
	 */
	void deleteAccount(string nationalID);




private:
	/***	signup	***/ // assistant functions 

	/**
	 * @brief handling for fullname
	 * @param string fullName
	 * @return bool(true if all name has letters, false if all name has not letters)
	 */
	bool checkFullname(string fullName);

	/**
	 * @brief handling for NationalID
	 * @param string nationalID
	 * @return bool(true if national id is 13 number , false if national id is not  13 number)
	 */
	bool cheakNationalID(string NationalID);

	/**
	 * @brief handling for password
	 * @param string password
	 * @return bool(true if password is 8 digits , false if password is not 8 digits)
	 */
	bool checkPassword(string password);
};


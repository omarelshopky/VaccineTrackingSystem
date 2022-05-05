#pragma once
#include "../../Models/Admin/Admin.h"
#include "../../Models/User/User.h"

class AdminController
{


public:
	AdminController();


	/**
	 * @brief make login for admin that stored in database
	 * @param string nationalID of the admin and string password of the admin
	 * @return bool shows if the login process for admin done successfully or not (true -> login be successfully, false -> login be failed )
	 */
	bool login(string nationalID, string password);


	/***	Merna	***/ 


	/**
	 * @brief Give Admin Privilege to a normal user
	 * @param string nationalID  of the user , string password to make him an admin
   */

	void giveAdminPrivilage(string nationalID , string password);


	/**
     * @brief View all the users that stored in the database
     * @return vector<User> contains the all stored users in the database
   */
	vector<User> viewUsers();


	/**
     * @brief Retrive specific user from the database according to his nationalID
     * @param string nationalID of the user
     * @return User which has the same nationalID
    */
	User viewUser(string nationalID);


	/**
     * @brief Delete all the users from the database
    */
	void deleteUsers();


	/**
	 * @brief Delete specific user from the database according to his nationalID
	 * @param string nationalID of the user
	*/
	void deleteUser(string nationalID);


<<<<<<< HEAD

	/***	Enas	***/ // LoginView
	vector<float> getStatistics();
=======
    /**
	* @brief gets the statistic about doses
	* @return map<string, float> -> the dose and its precentage 
	*/
	map<int, float> statOfAllDoses();


	/**
	* @brief gets the statistic about genders
	* @return map<string, float> -> the male and the precentage of its dose
	*/
	map<string, float> statOfAllGenders();


	/**
	* @brief to get the statistic about governments 
	* @return map<string, float> -> the govenment and the precentage of dose taken in
	*/
	map<string, float> statOfAllGovernment();
>>>>>>> 3534084063bcef43ba08386cd2a04cfcc9fc714f

private:
	/**
	* @brief gets the precntage of the spacific number of doses
	* @param int to select the number of doses
	* @return number -> the precentage of doses the user took 
	*/
	float statOfDoses(int numOfDoses);


	/**
	* @brief gets the precentage of the spacific number of males
	* @return number -> the precentage of males
	*/
	float statOfMale();


	/**
	* @brief gets the precentage of the spacific number of governments
	* @param string to select the government taken in
	* @return number -> the precentage of government
	*/
	float statOfGovernment(string government);


	/**
	* @brief gets the number of users in database
    * @return integer -> the precentage number of users
	*/
	int  numberOfUsers();
};


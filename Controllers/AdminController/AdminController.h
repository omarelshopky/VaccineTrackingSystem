#pragma once
#include "../../Models/Admin/Admin.h"
#include "../../Models/User/User.h"

class AdminController
{


public:

	/**
	 * @brief make login for admin that stored in database
	 * @param string nationalID of the admin and string password of the admin
	 * @return bool shows if the login process for admin done successfully or not (true -> login be successfully, false -> login be failed )
	 */
	bool login(string nationalID, string password);


	/**
	 * @brief Give Admin Privilege to a normal user
	 * @param string nationalID  of the user , string password to make him an admin
	 * @return bool determine wheather the process done successfully or not
    */
	bool giveAdminPrivilage(string nationalID , string password);


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


    /**
	* @brief Calculates statistic about users' Doses number
	* @return map<string, float> -> the dose and its precentage 
	*/
	map<int, int> statOfAllDoses();


	/**
	* @brief Calculates statistic about users' gender 
	* @return map<string, float> -> the male and the precentage of its dose
	*/
	map<string, int> statOfAllGenders();


	/**
	* @brief Calculates statistic about users' government
	* @return map<string, float> -> the govenment and the precentage of dose taken in
	*/
	map<string, int> statOfAllGovernments();


	/**
	* @brief Calculates statistic about users' age
	* @return map<string, float> -> the govenment and the precentage of dose taken in
	*/
	map<string, int> statOfAllAges();


	/**
	* @brief Calculate number of all registered users in database
	* @return int the count of user registered in the system
	*/
	int getAllUsersCount();
};


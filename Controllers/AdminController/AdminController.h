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


	/***	Merna	***/ // AdminPrivilageView
	void giveAdminPrivilage(string nationalID);
	vector<User> viewUsers();
	User viewUser(string nationalID);
	void deleteUsers();
	void deleteUser(string nationalID);


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


#pragma once
#include "../../Models/Admin/Admin.h"
#include "../../Models/User/User.h"

class AdminController
{


public:
	AdminController();

	/***	Doaa	***/
	void login(string nationalID, string password);


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



	/***	Enas	***/ // LoginView
	vector<float> getStatistics();

private:
	float statOfFirstDose();
	float statOfBothDose(); 
	float statOfNoDose();
	float statOfMale();
	float statOfGovernment(string government);

};


#pragma once
#include "../../Models/Admin/Admin.h"
#include "../../Models/User/User.h"

class AdminController
{


public:
	AdminController();

	/***	Doaa	***/
	void login(string nationalID, string password);


	/***	Merna	***/ // AdminPrivilageView
	void giveAdminPrivilage(string nationalID);
	vector<User> viewUsers();
	User viewUser(string nationalID);
	void deleteUsers();
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


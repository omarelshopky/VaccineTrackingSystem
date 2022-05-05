#include "UserController.h"

UserController::UserController() {

}


bool UserController::login(string nationalID, string password) {
	bool found = false;
	User user;
	vector <User> users = User::select();
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].nationalID == nationalID && users[i].password == password)
		{
			found = true;
		}
		if (found) {
			return true;
			break;
		}
		continue;
	}
	if (found == false) {
		return false;
	}

}


void UserController::deleteAccount(string nationalID) {
	User user;
	user.nationalID = nationalID;
	user.remove();
}
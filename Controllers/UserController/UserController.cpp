#include "UserController.h"


bool UserController::login(string nationalID, string password) {
	return User::select({ { "NationalID", "=", nationalID }, {"Password", "=", password} }).size();
}


void UserController::deleteAccount(string nationalID) {
	User user;
	user.nationalID = nationalID;
	user.remove();
}
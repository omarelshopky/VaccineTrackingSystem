#include "UserController.h"

UserController::UserController() {

}


void UserController::deleteAccount(string nationalID) {
	User user;
	user.nationalID = nationalID;
	user.remove();
}
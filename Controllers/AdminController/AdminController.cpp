#include "AdminController.h"





AdminController::AdminController() {

}


map<int, float> AdminController::statOfAllDoses() {
	map<int, float> info;
	for (int i = 0; i < 3; i++) {
		info[i] = statOfDoses(i);
	}
	return info;
}


float AdminController::statOfDoses(int numOfDoses) {
	vector<User> users = User::select({ { "DosesNumber", "=", (to_string(numOfDoses))} });
	return ((((float)users.size()) / ((float)numberOfUsers())) * 100);
}


map<string, float>  AdminController::statOfAllGenders() {
	map<string, float> info;
	info["Male"] = statOfMale();
	info["Female"] = (100 - info["Male"]);
	return info;
}


float AdminController::statOfMale() {
	vector<User> users = User::select({ {"Gender", "=", "Male"} });
	return (( ((float)users.size()) /((float) numberOfUsers())) * 100);
}


map<string,float> AdminController::statOfAllGovernment() {
	map<string, float> info;
	for (int i = 0; i < 22; i++) {
		info[governments[i]] = statOfGovernment(governments[i]);
	}
	return info;
}


float AdminController::statOfGovernment(string government) {
	vector<User> users = User::select({ { "Government", "=", government} });
	return (( (float)users.size() / (float)numberOfUsers()) * 100);
}


int AdminController::numberOfUsers() {
		return User::select({}).size();
}
 
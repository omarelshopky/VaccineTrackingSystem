#include "AdminController.h"
using namespace std;


bool AdminController::login(string nationalID, string password) {
	return Admin::select({ { "NationalID", "=", nationalID }, {"Password", "=", password} }).size();
}


vector<User> AdminController::viewUsers() {
	return User ::select();
}


User AdminController::viewUser(string nationalID) {
	vector<User> users = User::select({ {"NationalID" , "=" , nationalID } });

	if (!users.empty())
		return users.front();
	else
		return User();
}


void AdminController::deleteUsers() {
	vector<User> users = User::select();

	for (int i = 0; i < users.size(); i++) {
		users[i].remove();
	}
}


void AdminController::deleteUser(string nationalID) {
	User user;
	user.nationalID = nationalID;
	user.remove();
}


string AdminController::giveAdminPrivilage(string nationalID , string password) {
	vector<User> users = User::select({ {"NationalID" , "=" , nationalID } });

	if (!users.empty())
	{
		if (Admin::select({ {"NationalID" , "=" , nationalID } }).size() == 0) {
			Admin admin(users[0].nationalID, password);
			admin.insert();
			return "";
		}
		else {
			return "This user is already an admin";
		}	
	}
	else {
		return "There is no user with that National ID";
	}
} 


map<int, int> AdminController::statOfAllDoses() {
	map<int, int> info = {{ 0, 0 }, {1, 0}, {2, 0}};
	
	for (auto user : User::select()) {
		info[user.dosesNumber]++;
	}
	
	return info;
}


map<string, int>  AdminController::statOfAllGenders() {
	map<string, int> info = { {"Male", 0}, {"Female", 0} };

	for (auto user : User::select()) {
		info[user.gender]++;
	}

	return info;
}


map<string,int> AdminController::statOfAllGovernments() {
	map<string, int> info;

	for (int i = 0; i < 22; i++) info[governments[i]] = 0; // Initialize govs with 0

	for (auto user : User::select()) {
		info[user.government]++;
	}

	return info;
}


map<string, int> AdminController::statOfAllAges() {
	map<string, int> info = { {"5<>17", 0}, {"18<>30", 0}, {"31<>64", 0}, {"<65", 0} };

	for (auto users : User::select()) {
		if (users.age >= 5 && users.age <= 17) {
			info["5<>17"]++;
		}
		else if (users.age >= 18 && users.age <= 30) {
			info["18<>30"]++;
		}
		else if (users.age >= 31 && users.age <= 64) {
			info["31<>64"]++;
		}
		else if (users.age >= 65) {
			info["<65"]++;
		}
	}
	return info;
}


int AdminController::getAllUsersCount() {
	return User::select({}).size();
}
 

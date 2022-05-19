#include "AdminController.h"
using namespace std;


bool AdminController::login(string nationalID, string password) {
	return Admin::select({ { "NationalID", "=", nationalID }, {"Password", "=", password} }).size();
}


vector<User> AdminController::viewUsers() {

	vector<User> users = User ::select();
	
	for (int i = 0; i < users.size(); i++)
	{
		cout << "                    user number " << i + 1 << endl;
		cout <<  "  FullName : " << users[i].fullName << endl;
		cout  << "  NationalID : " << users[i].nationalID << endl;
		cout  << "  Password : " << users[i].password << endl;
		cout <<  "  Gender : " << users[i].gender << endl;
		cout <<  "  Age : " << users[i].age << endl;
		cout <<  "  Country : " << users[i].country << endl;
		cout <<  "  Government : " << users[i].government << endl;
		cout <<  "  isVaccinated : " << users[i].isVaccinated << endl;
		cout <<  "  DosesNumber : " << users[i].dosesNumber << endl;
		cout << "*******************************************************************************" << endl;
	}
	return users;
}


User AdminController::viewUser(string nationalID) {
	User user;
	bool found = false;
	vector<User> users = User::select();
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].nationalID == nationalID)
		{
			found = true;
			cout << "  the data of user which has nationalID -> " << users[i].nationalID << " is : " << endl;
			cout << "  FullName : " << users[i].fullName << endl;
			cout << "  NationalID : " << users[i].nationalID << endl;
			cout << "  Password : " << users[i].password << endl;
			cout << "  Gender : " << users[i].gender << endl;
			cout << "  Age : " << users[i].age << endl;
			cout << "  Country : " << users[i].country << endl;
			cout << "  Government : " << users[i].government << endl;
			cout << "  isVaccinated : " << users[i].isVaccinated << endl;
			cout << "  DosesNumber : " << users[i].dosesNumber << endl;
			cout << "*******************************************************************************" << endl;
			return users[i];
		}
	}
	
	if (found == false) {
		cout << " user not found , please enter a valid nationalID and try again :) " << endl;
		return user;
		}
		
}


void AdminController::deleteUsers() {
	vector<User> users = User::select();
	for (int i = 0; i < users.size(); i++) {
		users[i].remove();
		cout << "the data has been removed for user number : " << i+1 << endl;
	}

}


void AdminController::deleteUser(string nationalID) {
	bool found = false;
	vector<User> users = User::select();
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].nationalID == nationalID)
		{
			found = true;
		    users[i].remove();
		    cout << users[i].fullName << " " << "is removed " << endl;
		}
	}

	if (found == false) {
		cout << " user not found , please enter a valid nationalID and try again :) " << endl;
	}

}


void AdminController::giveAdminPrivilage(string nationalID , string password) {
	bool found = false;
	vector<User> users = User::select();
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].nationalID == nationalID)
		{
			found = true;
			Admin admin(users[i].nationalID, password);
			admin.insert();
			cout << "the user " << users[i].fullName << " is now an admin " << endl;
		}
	}

	if (found == false) {
		cout << " user  not found , try again " << endl;
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
 

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
 

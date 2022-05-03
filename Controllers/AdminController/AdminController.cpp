#include "AdminController.h"
using namespace std;


AdminController::AdminController() {

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



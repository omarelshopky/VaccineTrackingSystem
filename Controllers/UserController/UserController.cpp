#include "UserController.h"


bool UserController::checkFullname(string fullName)
{
	bool isValid = true;
	int words = 0;

	// Split string into words
	string attribute;
	vector<string> attributes;
	stringstream stream(fullName);

	// Loop over the string to get all its parts
	while (getline(stream, attribute, ' ')) {
		if (attribute != "") words++;

		for (int i = 0; i < attribute.length(); i++) {
			if (tolower(attribute[i]) >= 'a' && tolower(attribute[i]) <= 'z')
			{
				isValid = true;
			}
			else
			{
				isValid = false;
				break;
			}
		}

		if (isValid == false)
			break;
	}

	// User doesn't entered First and Last name at lest
	if (words < 2) isValid = false;

	return isValid;
}


bool UserController::cheakNationalID(string nationalID)
{
	bool isCorect = true;

	if (nationalID.length() != 14)
	{
		isCorect = false;
	}
	else
	{
		for (int i = 0; i < nationalID.length(); i++)
		{
			if (nationalID[i] >= '0' && nationalID[i] <= '9')
			{
				isCorect = true;
			}
			else
			{
				isCorect = false;
				break;
			}
		}
	}
	return isCorect;
}


bool UserController::checkPassword(string password)
{
	bool CorrectPassword = true;
	if (password.size() >= 8)
	{
		CorrectPassword = true;
	}
	else
	{
		CorrectPassword = false;
	}
	return CorrectPassword;
}


map<string, string> UserController::signup(string fullName, string nationalID, string password, string gender, int age, string country, string government, bool isVaccinated, int dosesNumber)
{
	map<string, string> regProblem;
	bool vaildData = true;						// vailData boolean to insert or Not 

	if (checkFullname(fullName))
	{
		regProblem["fullName"] = "";
	}
	else
	{
		regProblem["fullName"] = "Please Enter Valid Name!";
		vaildData = false;
	}


	if (cheakNationalID(nationalID))
	{
		regProblem["nationalID"] = "";
	}
	else
	{
		regProblem["nationalID"] = "Please Enter Valid 14 digits National ID!";
		vaildData = false;
	}

	if (checkPassword(password))
	{
		regProblem["password"] = "";
	}
	else
	{
		regProblem["password"] = "Please Enter Valid Password, 8-20 Digits!";
		vaildData = false;
	}

	if (vaildData)
	{
		User user(fullName, nationalID, password, gender, age, country, government, isVaccinated, dosesNumber);

		if (user.insert())
			regProblem["nationalID"] = "";
		else
			regProblem["nationalID"] = "You've entered duplicate national ID";
	}

	return regProblem;
}


bool UserController::login(string nationalID, string password) {
	return User::select({ { "NationalID", "=", nationalID }, {"Password", "=", password} }).size();
}


User UserController::display(string nationalId)
{
	return User::select({ {"NationalID", "=", nationalId} })[0];
}


map<string, string> UserController::edit(User user)
{
	map<string, string> state = { {"fullName", ""}, {"password", ""} };

	if (!checkFullname(user.fullName))
		state["fullName"] = "Please Enter Valid Name!";
	
	if (!checkPassword(user.password))
		state["password"] = "Please Enter Valid Password, 8-20 Digits!";

	if (state["fullName"] == "" && state["password"] == "") {
		user.update();
	}

	return state;
}


void UserController::deleteAccount(string nationalID) {
	User user;
	user.nationalID = nationalID;
	user.remove();
}
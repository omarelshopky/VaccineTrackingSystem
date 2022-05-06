#include "UserController.h"

bool UserController::checkFullname(string fullName)
{
	bool isLetter = true;

	for (int i = 0; i < fullName.length(); i++) {
		if (tolower(fullName[i]) >= 'a' && tolower(fullName[i]) <= 'z')
		{
			isLetter = true;
		}
		else
		{
			isLetter = false;
			break;
		}
	}
	return isLetter;
}



bool UserController::cheakNationalID(string nationalID)
{
	bool isCorect = true;

	if (nationalID.length() != 13)
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




map<string, string> UserController::signup(string fullName, string NationalID, string password, string gender, int age, string country, string government, bool isVaccinated, int dosesNumber)
{
	User userReg;

	map<string, string> regProblem;

	bool vaildData = true;						// vailData boolean to insert or Not 

	if (checkFullname(fullName))
	{
		regProblem["fullName"] = "";

	}
	else
	{
		regProblem["fullName"] = "please enter valid full name";
		vaildData = false;
	}



	if (cheakNationalID(NationalID))
	{
		regProblem["NationalID"] = "";
	}
	else
	{
		regProblem["NationalID"] = "please enter valid national ID";
		vaildData = false;
	}



	if (checkPassword(password))
	{
		regProblem["password"] = "";
	}
	else
	{
		regProblem["password"] = "please enter valid password, 8-20 digits ";
		vaildData = false;
	}

	userReg.gender = gender;
	userReg.age = age;
	userReg.country = country;
	userReg.isVaccinated = isVaccinated;

	if (isVaccinated == false)
		userReg.dosesNumber = 0;
	else
		userReg.dosesNumber = dosesNumber;

	if (vaildData)
	{
		if (userReg.insert())
			regProblem["duplicateNationalID"] = "";
		else
			regProblem["duplicateNationalID"] = "You've entered duplicate national ID";

	}

	return regProblem;
}

bool UserController::login(string nationalID, string password) {
	return User::select({ { "NationalID", "=", nationalID }, {"Password", "=", password} }).size();
}


void UserController::deleteAccount(string nationalID) {
	User user;
	user.nationalID = nationalID;
	user.remove();
}
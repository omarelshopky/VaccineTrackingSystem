#pragma once
#include "../../Core/Model/Model.h"

class User : public Model
{
	static FileHandler fileHandler;

public:
	string fullName;
	string nationalID;
	string password;
	string gender;
	int age;
	string country;
	string government;
	bool isVaccinated;
	int dosesNumber;


	User();

	User(string fullName, string NationalID, string password, string gender, int age, string country, string government, bool isVaccinated, int dosesNumber);


	/**
	* @breif Return the model primary key
	* @return string primary key of the mode
	*/
	string getPrimaryKey();


	/**
	 * @brief Retrive specific users from the database according to some conditions
	 * @param vector<condition> conditions to be applied into the records to filter them
	 * @return vector<User> contains the retrived users
	 */
	static vector<User> select(vector<condition> conditions = {});

private:
	/**
	 * @brief Convert the user object to map
	 * @return map<string, string> of the user attributes
	 */
	map<string, string> toMap();


	/**
	 * @brief Convert the user maped data to a user object
	 * @param map<string, string> data of the user
	 * @return User object obtained from the map
	 */
	static User fromMap(map<string, string> data);
};


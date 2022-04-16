#pragma once
#include "../../Core/FileHandler/FileHandler.h"


class Admin 
{
	static FileHandler fileHandler;

public:
	string nationalID;
	string password;

	Admin();

	Admin(string NationalID, string password);


	/**
	 * @brief Insert the Admin into the database
=	 * @return bool shows if the insertation process done successfully or not (true -> inserted successfully, false -> redundant National ID)
	 */
	bool insert();


	/**
	 * @brief Update the Admin in the database
	 */
	void update();


	/**
	 * @brief Remove the Admin from the database
	 */
	void remove();


	/**
	 * @brief Retrive specific admins from the database according to some conditions
	 * @param vector<condition> conditions to be applied into the records to filter them
	 * @return vector<Admin> contains the retrived admins
	 */
	static vector<Admin> select(vector<condition> conditions = {});

private:
	/**
	 * @brief Convert the admin object to map
	 * @return map<string, string> of the admin attributes
	 */
	map<string, string> toMap();


	/**
	 * @brief Convert the admin maped data to an admin object
	 * @param map<string, string> data of the admin
	 * @return Admin object obtained from the map
	 */
	static Admin fromMap(map<string, string> data);
};


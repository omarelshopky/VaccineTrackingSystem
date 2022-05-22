#pragma once
#include "../../Core/Model/Model.h"


class Admin : public Model
{
	static FileHandler fileHandler;

public:
	string nationalID;
	string password;

	Admin();

	Admin(string NationalID, string password);


	/**
	* @breif Return the model primary key
	* @return string primary key of the mode
	*/
	string getPrimaryKey();


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


#pragma once
/**
 * @file Model.h
 * @brief Handle file process (retriving, update and delete) which is the core for all the models
 */

#include "../../Config.h"
#include <map>
#include <vector>

class Model
{
public:
	string fileName;
	vector<string> headers;
	string primaryKey;

public:
	/**
	 * @brief Model Constructor
	 * @param string fileName containing the table data
	 * @param vector<string> headers of the table
	 * @param string primaryKey of the table
	 */
	Model(string fileName, vector<string> headers, string primaryKey);


	/**
	 * @brief Insert new record into the table
	 * @param map<string, string> data contains a value for each header in this table
	 * @return bool shows if the insertation process done successfully or not (true -> inserted successfully, false -> redundant primary key)
	 */
	bool insert(map<string, string> data);


	/**
	 * @brief Retrive specific records from the table according to some conditions
	 * @param vector<string> columns to be retrived from the database
	 * @param vector<condition> conditions to be applied into the records to filter them
	 * @return vector<map<string, string>> contains the retrived record each one in an index in the vector
	 */
	vector<map<string, string>> select(vector<string> columns, vector<condition> conditions);


	/**
	 * @brief Update specific records from the table according to some conditions
	 * @param map<string, string> data to be updated in the database
	 * @param vector<condition> conditions to be applied into the records to filter them
	 * @return int the number of records affected by the update process
	 */
	int update(map<string, string> data, vector<condition> conditions);


	/**
	 * @brief Remove specific records from the table according to some conditions
	 * @param vector<condition> conditions to be applied into the records to filter them
	 * @return int the number of records affected by the delete process
	 */
	int remove(vector<condition> conditions);

private:
	bool unique(string value);
};


#pragma once
/**
 * @file Model.h
 * @brief Handle file process (retriving, update and delete) which is the core for all the models
 */

#include "../../Config.h"


class FileHandler
{
	string filePath;

public:
	string primaryKey;
	vector<string> headers;


	/**
	 * @brief FileHandler Constructor
	 * @param string fileName containing the table data
	 * @param vector<string> headers of the table
	 * @param string primaryKey of the table
	 */
	FileHandler(string fileName, vector<string> headers, string primaryKey);


	/**
	 * @brief Insert new record into the table
	 * @param map<string, string> data contains a value for each header in this table
	 * @return bool shows if the insertation process done successfully or not (true -> inserted successfully, false -> redundant primary key)
	 */
	bool insert(map<string, string> data);


	/**
	 * @brief Retrive specific records from the table according to some conditions
	 * @param vector<condition> conditions to be applied into the records to filter them
	 * @return vector<map<string, string>> contains the retrived record each one in an index in the vector
	 */
	vector<map<string, string>> select(vector<condition> conditions);


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
	/**
	 * @brief Initialize the database file for the current table
	 */
	void initDB();


	/**
	 * @brief Append a line to the file
	 * @param string line that will be appended
	 */
	void appendLine(string line, ios_base::openmode mode = ios::app);


	/**
	 * @brief Read the file records to a vector of maps
	 * @return vector<map<string, string>> recoreds from the file
	 */
	vector<map<string, string>> readData();


	/**
	 * @brief Split the one line record string into a vector of strings
	 * @param string recordLine to be splited
	 * @return vector<string> of attributes after spliting process
	 */
	vector<string> splitRecord(string recordLine);


	/**
	 * @brief Checks if there is a record with this primary key or not
	 * @param string value of the primary ket
	 * @return bool determine the uniquness state (true -> there is no records has this primary key, false -> a record has this primary key already)
	 */
	bool isUnique(string value);


	/**
	 * @brief Save vector records to the its file
	 * @param vector<map<string, string>> records want to be saved to the file
	 */
	void saveData(vector<map<string, string>> records);


	/**
	 * @brief Evaluate specific condition over one record
	 * @param map<string, string> the record will be checked
	 * @param condition the condition to be evaluated
	 * @return bool evaluation resault (true -> success, false -> fail)
	 */
	bool checkCondition(map<string, string> record, condition condition);
};


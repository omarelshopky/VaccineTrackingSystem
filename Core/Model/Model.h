#pragma once
#include "../../Core/FileHandler/FileHandler.h"

class Model
{
	FileHandler* fileHandler;

public:
	Model(FileHandler *fileHandler);


	/**
	 * @brief Insert the record into the database
	 */
	bool insert();


	/**
	 * @brief Update the record in the database
	 */
	void update();


	/**
	 * @brief Remove the record from the database
	 */
	void remove();


	/**
	 * @brief Convert the model object to map
	 * @return map<string, string> of the model attributes
	 */
	virtual map<string, string> toMap() = 0;


	/**
	* @breif Return the model primary key
	* @return string primary key of the mode
	*/
	virtual string getPrimaryKey() = 0;
};


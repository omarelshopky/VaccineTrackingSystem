#pragma once
/***		Include Helper Libraries		***/
#include<iostream>


using namespace std;


/***				Enums				***/
typedef enum { MALE, FEMALE } gender_t;

/*****************************************/


/***				Structs				***/
struct condition {
	string key;
	string comparison;
	string value;
};

/*****************************************/


/***					Constants						***/
#define RECORD_SPLITER '|'

#define FILE_EXTENSION ".txt"

#define DATA_DIR_PATH "Data/"


/**********************************************************/


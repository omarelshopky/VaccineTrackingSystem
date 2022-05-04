#pragma once
/***		Include Helper Libraries		***/
#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>


using namespace std;


/***				Enums				***/
typedef enum { MALE, FEMALE } gender_t;
static string governments[] = { "Cairo", "Alexandria", "Aswan", "Asyut", "Beheira", "Beni Suef", "Dakahlia", "Damietta", "Faiyum", "Gharbia", "Giza", "Ismailia", 
				 		    "Kafr El Sheik", "Luxor", "Matruh", "Minya", "Monufia", "New Valley", "North Sinai", "Port Said", "Qalyubia", "Qena", "Red Sea",
							"Sharqia", "Sohag", "South", "Suez" };

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


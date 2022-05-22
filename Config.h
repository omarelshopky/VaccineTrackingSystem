#pragma once
/***		Include Helper Libraries		***/
#include<iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <unordered_map>


using namespace std;

/***				Constant				***/
const string mode = "development"; // "production", "development"

/**********************************************/


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


/***					Defination						***/
#define RECORD_SPLITER '|'

#define FILE_EXTENSION ".txt"

#define DATA_DIR_PATH "Data/"

#define LOGIN_VIEW_INDEX 0
#define REGISTER_VIEW_INDEX 1
#define USER_PROFILE_VIEW_INDEX 2
#define ADMIN_DASHBOARD_VIEW_INDEX 3
#define STATISTICS_VIEW_INDEX 4
#define ADMIN_PRIVILAGE_VIEW_INDEX 5
#define WAITING_LIST_VIEW_INDEX 6


/**********************************************************/


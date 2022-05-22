#include "Admin.h"


FileHandler Admin::fileHandler(
	"admin",
	{ "NationalID", "Password"},
	"NationalID"
);


Admin::Admin() : Model(&Admin::fileHandler) {
	nationalID = password = "";
};


Admin::Admin(string nationalID, string password) : nationalID(nationalID), password(password), Model(&Admin::fileHandler) {}


string Admin::getPrimaryKey() {
	return this->nationalID;
}


vector<Admin> Admin::select(vector<condition> conditions) {
	vector<map<string, string>> records = Admin::fileHandler.select(conditions);
	vector<Admin> admins;

	for (int i = 0; i < records.size(); i++) {
		admins.push_back(Admin::fromMap(records[i]));
	}

	return admins;
}


map<string, string> Admin::toMap() {
	return {
		{Admin::fileHandler.headers[0], this->nationalID},
		{Admin::fileHandler.headers[1], this->password}
	};
}


Admin Admin::fromMap(map<string, string> data) {
	return Admin(
		data[Admin::fileHandler.headers[0]],
		data[Admin::fileHandler.headers[1]]
	);
}
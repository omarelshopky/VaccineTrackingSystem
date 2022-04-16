#include "User.h"

FileHandler User::fileHandler(
	"user",
	{"FullName", "NationalID", "Password", "Gender", "Age", "Country", "Government", "isVaccinated", "DosesNumber"},
	"NationalID"
);


User::User() {
	fullName = nationalID = password = gender = country = government = "";
	age = isVaccinated = dosesNumber = 0;
};


User::User(string fullName, string nationalID, string password, string gender, 
	int age, string country, string government, bool isVaccinated, int dosesNumber) :
	fullName(fullName), nationalID(nationalID), password(password), gender(gender), 
	age(age), country(country), government(government), isVaccinated(isVaccinated), dosesNumber(dosesNumber) {}


bool User::insert() {
	return User::fileHandler.insert(this->toMap());
}


void User::update() {
	User::fileHandler.update(
		this->toMap(),
		{ {User::fileHandler.primaryKey, "=", this->nationalID} }
	);
}


void User::remove() {
	User::fileHandler.remove({ {User::fileHandler.primaryKey, "=", this->nationalID} });
}


vector<User> User::select(vector<condition> conditions) {
	vector<map<string, string>> records = User::fileHandler.select(conditions);
	vector<User> users;

	for (int i = 0; i < records.size(); i++) {
		users.push_back(User::fromMap(records[i]));
	}

	return users;
}


map<string, string> User::toMap() {
	return {
		{User::fileHandler.headers[0], this->fullName},
		{User::fileHandler.headers[1], this->nationalID},
		{User::fileHandler.headers[2], this->password},
		{User::fileHandler.headers[3], this->gender},
		{User::fileHandler.headers[4], to_string(this->age)},
		{User::fileHandler.headers[5], this->country},
		{User::fileHandler.headers[6], this->government},
		{User::fileHandler.headers[7], to_string(this->isVaccinated)},
		{User::fileHandler.headers[8], to_string(this->dosesNumber)}
	};
}


User User::fromMap(map<string, string> data) {
	return User(
		data[User::fileHandler.headers[0]],
		data[User::fileHandler.headers[1]],
		data[User::fileHandler.headers[2]],
		data[User::fileHandler.headers[3]],
		stoi(data[User::fileHandler.headers[4]]),
		data[User::fileHandler.headers[5]],
		data[User::fileHandler.headers[6]],
		stoi(data[User::fileHandler.headers[7]]),
		stoi(data[User::fileHandler.headers[8]])
	);
}
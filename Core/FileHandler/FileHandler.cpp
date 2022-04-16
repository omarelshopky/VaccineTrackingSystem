#include "FileHandler.h"


FileHandler::FileHandler(string fileName, vector<string> headers, string primaryKey) : 
	filePath(DATA_DIR_PATH + fileName + FILE_EXTENSION),headers(headers), primaryKey(primaryKey) {

    ifstream file;

    file.open(filePath);

    // Check if there is already a file for this table
    if (file) { 
        file.close();
    }
    else {
        initDB();
    }
}


void FileHandler::initDB() {
    
    // Arrange headers line for this table
    string headersLine = this->headers[0];
    
    for (int i = 1; i < this->headers.size(); i++) {
        headersLine += RECORD_SPLITER + this->headers[i];
    }
    
    this->appendLine(headersLine, ios::out);
}


void FileHandler::appendLine(string line, ios_base::openmode mode) {
    ofstream file;

    file.open(this->filePath, mode);

    file << line << "\n";

    file.close();
}


bool FileHandler::insert(map<string, string> data) {

    // Check primary key violation
    if (data[this->primaryKey] != "" && isUnique(data[this->primaryKey])) {
        // Arrange the record as a one line string
        string record = data[this->headers[0]];

        for (int i = 1; i < this->headers.size(); i++) {
            record += RECORD_SPLITER + data[this->headers[i]];
        }

        // Append the record to the file
        this->appendLine(record);

        return true;
    }
    else {
        return false;
    }
}


vector<string> FileHandler::splitRecord(string recordLine) {
    string attribute;  
    vector<string> attributes;
    stringstream stream(recordLine); 

    // Loop over the string to get all its parts
    while (getline(stream, attribute, RECORD_SPLITER)) {
        attributes.push_back(attribute);
    }

    return attributes;
}


vector<map<string, string>> FileHandler::readData() {
    vector<map<string, string>> records;
    string recordLine;
    ifstream file;

    file.open(this->filePath);

    getline(file, recordLine); // Ignore headers line

    while (file) {
        getline(file, recordLine); // Read line from the file

        vector<string> attributes = this->splitRecord(recordLine); // extract attribues from the line

        // Convert the record to map
        map<string, string> record;

        for (int i = 0; i < attributes.size(); i++) {
            record[this->headers[i]] = attributes[i];
        }

        records.push_back(record);
    }
    records.pop_back(); // Remove the last empty line

    return records;
}


vector<map<string, string>> FileHandler::select(vector<condition> conditions = {}) {
    vector<map<string, string>> allRecords = this->readData();
    vector<map<string, string>> retrivedRecords;

    if (conditions.size() == 0) // Select * (all) records
        return allRecords;

    for (int i = 0; i < allRecords.size(); i++) {
        bool valid = true;

        for (int j = 0; j < conditions.size(); j++) {
            if (!this->checkCondition(allRecords[i], conditions[j])) {
                valid = false;
                break;
            }
        }

        if (valid) {
            retrivedRecords.push_back(allRecords[i]);
        }
    }

    return retrivedRecords;
}


bool FileHandler::isUnique(string value) {
    return !(this->select({ {this->primaryKey, "=", value} }).size());
}


int FileHandler::update(map<string, string> data, vector<condition> conditions) {
    int affectedRecords = 0;
    vector<map<string, string>> records = this->readData();

    for (int i = 0; i < records.size(); i++) {
        bool valid = true;

        // Evaluate all conditions
        for (int j = 0; j < conditions.size(); j++) {
            if (!this->checkCondition(records[i], conditions[j])) {
                valid = false;
                break;
            }
        }

        // Update when the record is valid
        if (valid) {
            for (map<string, string>::iterator it = data.begin(); it != data.end(); ++it) {
                if (it->first != this->primaryKey || (it->first == this->primaryKey && this->isUnique(it->second))) {
                    records[i][it->first] = it->second;
                } 
            }

            affectedRecords++;
        }
    }
    
    this->saveData(records);

    return affectedRecords;
}


void FileHandler::saveData(vector<map<string, string>> records) {
    this->initDB(); // Clear the file

    ofstream file;

    file.open(this->filePath, ios::app);

    for (int i = 0; i < records.size(); i++) {
        // Arrange the record as a one line string
        string record = records[i][this->headers[0]];

        for (int j = 1; j < this->headers.size(); j++) {
            record += RECORD_SPLITER + records[i][this->headers[j]];
        }

        file << record << "\n";
    }

    file.close();
}


bool FileHandler::checkCondition(map<string, string> record, condition condition) {
    if (condition.comparison == "=") {
        if (!(record[condition.key] == condition.value))
            return false;
    }
    else if (condition.comparison == ">") {
        if (!(record[condition.key] > condition.value)) 
            return false;
    }
    else if (condition.comparison == ">=") {
        if (!(record[condition.key] >= condition.value)) 
            return false;
    }
    else if (condition.comparison == "<") {
        if (!(record[condition.key] < condition.value)) 
            return false;
    }
    else if (condition.comparison == "<=") {
        if (!(record[condition.key] <= condition.value)) 
            return false;
    }
    else if (condition.comparison == "!=") {
        if (!(record[condition.key] != condition.value)) 
            return false;
    }

    return true;
}


int FileHandler::remove(vector<condition> conditions) {
    int affectedRecords = 0;
    vector<map<string, string>> records = this->readData();
    vector<map<string, string>> remainRecords;

    for (int i = 0; i < records.size(); i++) {
        bool valid = true;

        // Evaluate all conditions
        for (int j = 0; j < conditions.size(); j++) {
            if (!this->checkCondition(records[i], conditions[j])) {
                valid = false;
                break;
            }
        }

        // Update when the record is valid
        if (valid) {
            affectedRecords++;
        }
        else {
            remainRecords.push_back(records[i]);
        }
    }

    this->saveData(remainRecords);

    return affectedRecords;
}
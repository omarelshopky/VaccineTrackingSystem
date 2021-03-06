#include "FileHandler.h"

FileHandler::FileHandler() {};

FileHandler::FileHandler(string fileName, vector<string> headers, string primaryKey) : 
	filePath(DATA_DIR_PATH + fileName + FILE_EXTENSION),headers(headers), primaryKey(primaryKey) {

    data = readData();

    if (data.size() == 0) initDB();
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
        this->data[data[primaryKey]] = data;

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


unordered_map<string, map<string, string>> FileHandler::readData() {
    unordered_map<string, map<string, string>> records;
    string recordLine;
    ifstream file;

    file.open(this->filePath);

    // Return empty vector when there is no file for this table
    if (!file) return {}; 

    getline(file, recordLine); // Ignore headers line

    while (file) {
        getline(file, recordLine); // Read line from the file

        if (recordLine != "") {
            vector<string> attributes = this->splitRecord(recordLine); // extract attribues from the line

            // Convert the record to map
            map<string, string> record;

            for (int i = 0; i < attributes.size(); i++) {
                record[this->headers[i]] = attributes[i];
            }

            records[record[primaryKey]] = record;
        }
    }
    file.close();

    return records;
}


vector<map<string, string>> FileHandler::select(vector<condition> conditions = {}) {
    vector<map<string, string>> retrivedRecords;
    
    if (conditions.size() == 0) // Select * (all) records
        return convertDataToVector();

    if (conditions.size() == 1 && conditions[0].key == primaryKey && conditions[0].comparison == "=") {
        if (data[conditions[0].value][primaryKey] != "") return { data[conditions[0].value] };
        else return {};
    }

    for (auto record : data) {
        bool valid = true;

        for (int j = 0; j < conditions.size(); j++) {
            if (!this->checkCondition(record.second, conditions[j])) {
                valid = false;
                break;
            }
        }

        if (valid) {
            retrivedRecords.push_back(record.second);
        }
    }

    return retrivedRecords;
}


bool FileHandler::isUnique(string value) {
    return !(this->select({ {this->primaryKey, "=", value} }).size());
}


int FileHandler::update(map<string, string> data, vector<condition> conditions) {
    int affectedRecords = 0;

    /*if (conditions.size() == 1 && conditions[0].key == primaryKey && conditions[0].comparison == "=") {
        if (this->data[conditions[0].value][primaryKey] != "") {
            for (map<string, string>::iterator it = data.begin(); it != data.end(); ++it) {
                if ((it->first != this->primaryKey || (it->first == this->primaryKey && this->isUnique(it->second))) && it->second != "") {
                    this->data[conditions[0].value][it->first] = it->second;
                }
            }

            this->saveData();
            return 1;
        }
    }*/


    for (auto record : this->data) {
        bool valid = true;

        // Evaluate all conditions
        for (int j = 0; j < conditions.size(); j++) {
            if (!this->checkCondition(record.second, conditions[j])) {
                valid = false;
                break;
            }
        }

        // Update when the record is valid
        if (valid) {
            for (map<string, string>::iterator it = data.begin(); it != data.end(); ++it) {
                if ((it->first != this->primaryKey || (it->first == this->primaryKey && this->isUnique(it->second))) && it->second != "") {
                    record.second[it->first] = it->second;
                } 
            }

            affectedRecords++;
        }
    }
    
    this->saveData();

    return affectedRecords;
}


void FileHandler::saveData() {
    this->initDB(); // Clear the file

    ofstream file;

    file.open(this->filePath, ios::app);

    for (auto record : data) {
        // Arrange the record as a one line string
        string lineRecord = record.second[this->headers[0]];

        for (int j = 1; j < this->headers.size(); j++) {
            lineRecord += RECORD_SPLITER + record.second[this->headers[j]];
        }

        file << lineRecord << "\n";
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

    if (conditions.size() == 1 && conditions[0].key == primaryKey && conditions[0].comparison == "=") {
        data.erase(conditions[0].value);
        this->saveData();
        return 1;
    }

    for (auto record : data) {
        bool valid = true;

        // Evaluate all conditions
        for (int j = 0; j < conditions.size(); j++) {
            if (!this->checkCondition(record.second, conditions[j])) {
                valid = false;
                break;
            }
        }

        // Update when the record is valid
        if (valid) {
            data.erase(record.first);
            affectedRecords++;
        }
    }

    this->saveData();

    return affectedRecords;
}


vector<map<string, string>> FileHandler::convertDataToVector() {
    vector<map<string, string>> records;

    for (auto record : data) {
        records.push_back(record.second);
    }

    return records;
}
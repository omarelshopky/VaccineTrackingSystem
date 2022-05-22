#include "Model.h"

Model::Model(FileHandler* fileHandler) {
	Model::fileHandler = fileHandler;
};


bool Model::insert() {
	return Model::fileHandler->insert(this->toMap());
}


void Model::update() {
	Model::fileHandler->update(
		this->toMap(),
		{ {Model::fileHandler->primaryKey, "=", this->getPrimaryKey()} }
	);
}


void Model::remove() {
	Model::fileHandler->remove({ {Model::fileHandler->primaryKey, "=", this->getPrimaryKey()} });
}

#include "Item.h"

Item::Item(int id, const std::string &nome) : id(id), nome(nome) {}

int Item::getId() const {
	return id;
}

const std::string &Item::getNome() const {
	return nome;
}

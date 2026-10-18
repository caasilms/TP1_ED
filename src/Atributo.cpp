#include "Atributo.h"

Atributo::Atributo(int id, const std::string &nome) : id(id), nome(nome) {}

int Atributo::getId() const {
	return id;
}

const std::string &Atributo::getNome() const {
	return nome;
}

#include "Aventureiro.h"

Aventureiro::Aventureiro(int id, const std::string &nome) : id(id), nome(nome) {}

int Aventureiro::getId() const {
	return id;
}

const std::string &Aventureiro::getNome() const {
	return nome;
}
Pilha& Aventureiro::getBuild() { return build; }

#include <string>
#include "Pilha.h"
#ifndef AVENTUREIRO_HPP
#define AVENTUREIRO_HPP

class Aventureiro {
    private:
    int id;
    std::string nome;
    Pilha build;

public:
    Aventureiro(int id, const std::string &nome);
    int getId() const;
    const std::string &getNome() const;
    Pilha& getBuild();
};

#endif

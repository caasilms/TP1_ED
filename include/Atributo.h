#include <string>
#ifndef ATRIBUTO_HPP
#define ATRIBUTO_HPP

class Atributo
{
private:
    int id;
    std::string nome;

public:
    Atributo(int id, const std::string &nome);
    int getId() const;
    const std::string &getNome() const;
};

#endif
#include <string>
#ifndef ITEM_HPP
#define ITEM_HPP

class Item
{
private:
    int id;
    std::string nome;

public:
    Item(int id, const std::string &nome);
    int getId() const;
    const std::string &getNome() const;
};

#endif

#include <string>
#include "Aventureiro.h"
#include "Atributo.h"
#include "Item.h"
#include "No.h"
#include "Catalogo.h"
#include "Fila.h"
#ifndef SISTEMA_HPP
#define SISTEMA_HPP

class Sistema {
private:
    No<Atributo>* atributos;
    int qtdAtributos;

    No<Item>* itens;
    int qtdItens;

    No<Aventureiro>* aventureiros;
    int qtdAventureiros;
    Catalogo catalogo;
    Fila fila;
    No<Atributo>* atributoPorId(int id) const;
    No<Item>* itemPorId(int id) const;
    No<Aventureiro>* aventureiroPorId(int id) const;
    void processarLinha(const std::string& linha);

public:
    Sistema();
    Sistema(const Sistema&) = delete;
    Sistema& operator=(const Sistema&) = delete;
    void cadastrarAtributo(std::string nome);
    void cadastrarItem(std::string nome);
    void cadastrarAventureiro(std::string nome);
    void executar();
    ~Sistema();
};
#endif

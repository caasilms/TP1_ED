#ifndef FILA_HPP
#define FILA_HPP

struct Encomenda { int idAventureiro; int idItem; };

class Fila {
private:
    struct No { Encomenda valor; No* prox; };
    No* inicio;
    No* fim;
    int tamanho;
public:
    Fila();
    ~Fila();
    Fila(const Fila&) = delete;
    Fila& operator=(const Fila&) = delete;
    int enfileirar(int idAventureiro, int idItem);
    bool desenfileirar(Encomenda& e);
    bool vazia() const;
};

#endif

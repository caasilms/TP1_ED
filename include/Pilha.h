#ifndef PILHA_HPP
#define PILHA_HPP

class Pilha {
private:
    struct No { int idItem; No* prox; };
    No* topo;
public:
    Pilha();
    ~Pilha();
    Pilha(const Pilha& outra);
    Pilha& operator=(const Pilha& outra);
    void empilhar(int idItem);
    bool desempilhar(int& idItem);
    bool vazia() const;
};

#endif

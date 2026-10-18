#ifndef CATALOGO_HPP
#define CATALOGO_HPP

class Catalogo {
private:
    struct Celula {
        int idItem;
        int idAtributo;
        int valor;
        Celula* proximaLinha;
        Celula* proximaColuna;
    };

    struct Tripleta {
        int idItem;
        int idAtributo;
        int valor;
    };

    char modo;
    Celula** linhas;
    Celula** colunas;
    int capacidadeLinhas;
    int capacidadeColunas;
    Tripleta* tripletas;
    int tamanhoTripletas;
    int capacidadeTripletas;

    void garantirCabecas(int idItem, int idAtributo);
    void garantirTripletas();
    void limparListaCruzada();
    void definirEmLista(int idItem, int idAtributo, int valor);
    void definirEmTripletas(int idItem, int idAtributo, int valor);

public:
    Catalogo();
    ~Catalogo();
    Catalogo(const Catalogo&) = delete;
    Catalogo& operator=(const Catalogo&) = delete;
    void definir(int idItem, int idAtributo, int valor);
    int consultar(int idItem, int idAtributo) const;
    void trocarModo(char novoModo);
    char getModo() const;
    struct Entrada { int id; int valor; };
    int percorrerLinha(int idItem, Entrada* saida, int max) const;
    int percorrerColuna(int idAtributo, Entrada* saida, int max) const;
    int quantidadeLinha(int idItem) const;
    int quantidadeColuna(int idAtributo) const;
    double produtoInternoLinhas(int itemA, int itemB) const;
};

#endif

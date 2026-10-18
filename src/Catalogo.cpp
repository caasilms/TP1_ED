#include "Catalogo.h"

Catalogo::Catalogo()
    : modo('L'), linhas(nullptr), colunas(nullptr),
      capacidadeLinhas(0), capacidadeColunas(0), tripletas(nullptr),
      tamanhoTripletas(0), capacidadeTripletas(0) {}

Catalogo::~Catalogo() {
    limparListaCruzada();
    delete[] tripletas;
    delete[] linhas;
    delete[] colunas;
}

void Catalogo::garantirCabecas(int idItem, int idAtributo) {
    if (idItem >= capacidadeLinhas) {
        int novaCapacidade = capacidadeLinhas == 0 ? 1 : capacidadeLinhas;
        while (novaCapacidade <= idItem) novaCapacidade *= 2;
        Celula** novasLinhas = new Celula*[novaCapacidade];
        for (int i = 0; i < novaCapacidade; i++)
            novasLinhas[i] = i < capacidadeLinhas ? linhas[i] : nullptr;
        delete[] linhas;
        linhas = novasLinhas;
        capacidadeLinhas = novaCapacidade;
    }
    if (idAtributo >= capacidadeColunas) {
        int novaCapacidade = capacidadeColunas == 0 ? 1 : capacidadeColunas;
        while (novaCapacidade <= idAtributo) novaCapacidade *= 2;
        Celula** novasColunas = new Celula*[novaCapacidade];
        for (int i = 0; i < novaCapacidade; i++)
            novasColunas[i] = i < capacidadeColunas ? colunas[i] : nullptr;
        delete[] colunas;
        colunas = novasColunas;
        capacidadeColunas = novaCapacidade;
    }
}

void Catalogo::garantirTripletas() {
    if (tamanhoTripletas < capacidadeTripletas) return;
    int novaCapacidade = capacidadeTripletas == 0 ? 1 : capacidadeTripletas * 2;
    Tripleta* novasTripletas = new Tripleta[novaCapacidade];
    for (int i = 0; i < tamanhoTripletas; i++) novasTripletas[i] = tripletas[i];
    delete[] tripletas;
    tripletas = novasTripletas;
    capacidadeTripletas = novaCapacidade;
}

void Catalogo::limparListaCruzada() {
    for (int i = 0; i < capacidadeLinhas; i++) {
        Celula* atual = linhas[i];
        while (atual != nullptr) {
            Celula* proxima = atual->proximaLinha;
            delete atual;
            atual = proxima;
        }
        linhas[i] = nullptr;
    }
    for (int i = 0; i < capacidadeColunas; i++) colunas[i] = nullptr;
}

void Catalogo::definirEmLista(int idItem, int idAtributo, int valor) {
    garantirCabecas(idItem, idAtributo); 
    Celula* anteriorLinha = nullptr;
    Celula* atual = linhas[idItem];
    while (atual != nullptr && atual->idAtributo < idAtributo) {
        anteriorLinha = atual;
        atual = atual->proximaLinha;
    }
    if (atual != nullptr && atual->idAtributo == idAtributo) {
        if (valor != 0) {
            atual->valor = valor;
            return;
        }
        if (anteriorLinha == nullptr) linhas[idItem] = atual->proximaLinha;
        else anteriorLinha->proximaLinha = atual->proximaLinha;
        Celula* anteriorColuna = nullptr;
        Celula* coluna = colunas[idAtributo];
        while (coluna != atual) {
            anteriorColuna = coluna;
            coluna = coluna->proximaColuna;
        }
        if (anteriorColuna == nullptr) colunas[idAtributo] = coluna->proximaColuna;
        else anteriorColuna->proximaColuna = coluna->proximaColuna;
        delete atual;
        return;
    }
    if (valor == 0) return;
    Celula* nova = new Celula{idItem, idAtributo, valor, atual, nullptr};
    if (anteriorLinha == nullptr) linhas[idItem] = nova;
    else anteriorLinha->proximaLinha = nova;
    Celula* anteriorColuna = nullptr;
    Celula* coluna = colunas[idAtributo];
    while (coluna != nullptr && coluna->idItem < idItem) {
        anteriorColuna = coluna;
        coluna = coluna->proximaColuna;
    }
    nova->proximaColuna = coluna;
    if (anteriorColuna == nullptr) colunas[idAtributo] = nova;
    else anteriorColuna->proximaColuna = nova;
}

void Catalogo::definirEmTripletas(int idItem, int idAtributo, int valor) {
    int esquerda = 0;
    int direita = tamanhoTripletas;
    while (esquerda < direita) {
        int meio = (esquerda + direita) / 2;
        if (tripletas[meio].idItem < idItem ||
            (tripletas[meio].idItem == idItem && tripletas[meio].idAtributo < idAtributo))
            esquerda = meio + 1;
        else direita = meio;
    }
    bool existe = esquerda < tamanhoTripletas &&
        tripletas[esquerda].idItem == idItem &&
        tripletas[esquerda].idAtributo == idAtributo;
    if (existe) {
        if (valor == 0) {
            for (int i = esquerda; i + 1 < tamanhoTripletas; i++) tripletas[i] = tripletas[i + 1];
            tamanhoTripletas--;
        } else tripletas[esquerda].valor = valor;
        return;
    }
    if (valor == 0) return;
    garantirTripletas();
    for (int i = tamanhoTripletas; i > esquerda; i--) tripletas[i] = tripletas[i - 1];
    tripletas[esquerda] = {idItem, idAtributo, valor};
    tamanhoTripletas++;
}

void Catalogo::definir(int idItem, int idAtributo, int valor) {
    if (idItem < 0 || idAtributo < 0) return;
    if (modo == 'L') definirEmLista(idItem, idAtributo, valor);
    else definirEmTripletas(idItem, idAtributo, valor);
}

int Catalogo::consultar(int idItem, int idAtributo) const {
    if (idItem < 0 || idAtributo < 0) return 0;
    if (modo == 'L') {
        if (idItem >= capacidadeLinhas) return 0;
        Celula* atual = linhas[idItem];
        while (atual != nullptr && atual->idAtributo < idAtributo) atual = atual->proximaLinha;
        return atual != nullptr && atual->idAtributo == idAtributo ? atual->valor : 0;
    }
    int esquerda = 0;
    int direita = tamanhoTripletas;
    while (esquerda < direita) {
        int meio = (esquerda + direita) / 2;
        if (tripletas[meio].idItem < idItem ||
            (tripletas[meio].idItem == idItem && tripletas[meio].idAtributo < idAtributo))
            esquerda = meio + 1;
        else direita = meio;
    }
    return esquerda < tamanhoTripletas && tripletas[esquerda].idItem == idItem &&
        tripletas[esquerda].idAtributo == idAtributo ? tripletas[esquerda].valor : 0;
}

void Catalogo::trocarModo(char novoModo) {
    if ((novoModo != 'L' && novoModo != 'T') || novoModo == modo) return;
    if (novoModo == 'T') {
        // Constrói as tripletas a partir das linhas antes de descartar a lista.
        delete[] tripletas;
        tripletas = nullptr;
        tamanhoTripletas = 0;
        capacidadeTripletas = 0;
        for (int i = 0; i < capacidadeLinhas; i++) {
            Celula* atual = linhas[i];
            while (atual != nullptr) {
                definirEmTripletas(atual->idItem, atual->idAtributo, atual->valor);
                atual = atual->proximaLinha;
            }
        }
        limparListaCruzada();
    } else {
        Tripleta* antigas = tripletas;
        for (int i = 0; i < tamanhoTripletas; i++)
            definirEmLista(antigas[i].idItem, antigas[i].idAtributo, antigas[i].valor);
        tripletas = nullptr;
        tamanhoTripletas = 0;
        capacidadeTripletas = 0;
        delete[] antigas;
    }
    modo = novoModo;
}

char Catalogo::getModo() const {
    return modo;
}

int Catalogo::quantidadeLinha(int idItem) const {
    int n=0;
    if (modo=='L') { if(idItem<0||idItem>=capacidadeLinhas)return 0; for(Celula*p=linhas[idItem];p;p=p->proximaLinha)++n; }
    else for(int i=0;i<tamanhoTripletas;i++) if(tripletas[i].idItem==idItem)++n;
    return n;
}
int Catalogo::quantidadeColuna(int idAtributo) const {
    int n=0;
    if (modo=='L') { if(idAtributo<0||idAtributo>=capacidadeColunas)return 0; for(Celula*p=colunas[idAtributo];p;p=p->proximaColuna)++n; }
    else for(int i=0;i<tamanhoTripletas;i++) if(tripletas[i].idAtributo==idAtributo)++n;
    return n;
}
int Catalogo::percorrerLinha(int idItem, Entrada* saida, int max) const {
    int n=0;
    if(modo=='L') { if(idItem<0||idItem>=capacidadeLinhas)return 0; for(Celula*p=linhas[idItem];p;p=p->proximaLinha){if(saida&&n<max){saida[n].id=p->idAtributo;saida[n].valor=p->valor;}++n;} }
    else for(int i=0;i<tamanhoTripletas;i++) if(tripletas[i].idItem==idItem){if(saida&&n<max){saida[n].id=tripletas[i].idAtributo;saida[n].valor=tripletas[i].valor;}++n;}
    return n;
}
int Catalogo::percorrerColuna(int idAtributo, Entrada* saida, int max) const {
    int n=0;
    if(modo=='L') { if(idAtributo<0||idAtributo>=capacidadeColunas)return 0; for(Celula*p=colunas[idAtributo];p;p=p->proximaColuna){if(saida&&n<max){saida[n].id=p->idItem;saida[n].valor=p->valor;}++n;} }
    else for(int i=0;i<tamanhoTripletas;i++) if(tripletas[i].idAtributo==idAtributo){if(saida&&n<max){saida[n].id=tripletas[i].idItem;saida[n].valor=tripletas[i].valor;}++n;}
    return n;
}

double Catalogo::produtoInternoLinhas(int itemA, int itemB) const {
    int nA=quantidadeLinha(itemA), nB=quantidadeLinha(itemB);
    Entrada* a=new Entrada[nA?nA:1];
    Entrada* b=new Entrada[nB?nB:1];
    percorrerLinha(itemA,a,nA); percorrerLinha(itemB,b,nB);
    int i=0,j=0; double soma=0;
    while(i<nA&&j<nB) {
        if(a[i].id==b[j].id) { soma+=(double)a[i].valor*b[j].valor; ++i; ++j; }
        else if(a[i].id<b[j].id) ++i;
        else ++j;
    }
    delete[]a; delete[]b;
    return soma;
}

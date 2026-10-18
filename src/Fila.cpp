#include "Fila.h"
Fila::Fila():inicio(nullptr),fim(nullptr),tamanho(0){}
Fila::~Fila(){Encomenda e;while(desenfileirar(e)){} }
int Fila::enfileirar(int h,int i){No*n=new No{{h,i},nullptr};if(fim)fim->prox=n;else inicio=n;fim=n;return ++tamanho;}
bool Fila::desenfileirar(Encomenda&e){if(!inicio)return false;No*n=inicio;e=n->valor;inicio=n->prox;if(!inicio)fim=nullptr;delete n;--tamanho;return true;}
bool Fila::vazia()const{return inicio==nullptr;}

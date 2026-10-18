#include "Pilha.h"
Pilha::Pilha():topo(nullptr){}
Pilha::Pilha(const Pilha& outra):topo(nullptr){No* rev=nullptr;for(No*p=outra.topo;p;p=p->prox)rev=new No{p->idItem,rev};while(rev){empilhar(rev->idItem);No*n=rev;rev=rev->prox;delete n;}}
Pilha& Pilha::operator=(const Pilha& outra){if(this==&outra)return *this;int x;while(desempilhar(x)){}No* rev=nullptr;for(No*p=outra.topo;p;p=p->prox)rev=new No{p->idItem,rev};while(rev){empilhar(rev->idItem);No*n=rev;rev=rev->prox;delete n;}return *this;}
Pilha::~Pilha(){int x;while(desempilhar(x)){} }
void Pilha::empilhar(int id){No*n=new No{id,topo};topo=n;}
bool Pilha::desempilhar(int& id){if(!topo)return false;No*n=topo;id=n->idItem;topo=n->prox;delete n;return true;}
bool Pilha::vazia()const{return topo==nullptr;}

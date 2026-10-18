#include "Sistema.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>

Sistema::Sistema() : atributos(nullptr), qtdAtributos(0), itens(nullptr),
    qtdItens(0), aventureiros(nullptr), qtdAventureiros(0) {}

void Sistema::cadastrarAtributo(std::string nome) {
    No<Atributo>* novo = new No<Atributo>(Atributo(qtdAtributos, nome));
    if (!atributos) atributos = novo;
    else { No<Atributo>* p=atributos; while(p->getProximo()) p=p->getProximo(); p->setProximo(novo); }
    ++qtdAtributos;
}
void Sistema::cadastrarItem(std::string nome) {
    No<Item>* novo = new No<Item>(Item(qtdItens, nome));
    if (!itens) itens = novo;
    else { No<Item>* p=itens; while(p->getProximo()) p=p->getProximo(); p->setProximo(novo); }
    ++qtdItens;
}
void Sistema::cadastrarAventureiro(std::string nome) {
    No<Aventureiro>* novo = new No<Aventureiro>(Aventureiro(qtdAventureiros, nome));
    if (!aventureiros) aventureiros = novo;
    else { No<Aventureiro>* p=aventureiros; while(p->getProximo()) p=p->getProximo(); p->setProximo(novo); }
    ++qtdAventureiros;
}
No<Atributo>* Sistema::atributoPorId(int id) const { No<Atributo>*p=atributos; while(p&&p->getValor().getId()!=id)p=p->getProximo(); return p; }
No<Item>* Sistema::itemPorId(int id) const { No<Item>*p=itens; while(p&&p->getValor().getId()!=id)p=p->getProximo(); return p; }
No<Aventureiro>* Sistema::aventureiroPorId(int id) const { No<Aventureiro>*p=aventureiros; while(p&&p->getValor().getId()!=id)p=p->getProximo(); return p; }

Sistema::~Sistema() {
    while(atributos){No<Atributo>*p=atributos->getProximo();delete atributos;atributos=p;}
    while(itens){No<Item>*p=itens->getProximo();delete itens;itens=p;}
    while(aventureiros){No<Aventureiro>*p=aventureiros->getProximo();delete aventureiros;aventureiros=p;}
}

void Sistema::executar() {
    std::string linha;
    while(std::getline(std::cin,linha)) processarLinha(linha);
}

void Sistema::processarLinha(const std::string& linha) {
    std::istringstream in(linha);
    std::string cmd;
    if(!(in>>cmd)) return;

    if(cmd=="E") { char modo; in>>modo; catalogo.trocarModo(modo); std::cout<<"E "<<modo<<"\n"; }
    else if(cmd=="A") { std::string nome;in>>nome;cadastrarAtributo(nome);std::cout<<"A "<<qtdAtributos-1<<"\n"; }
    else if(cmd=="I") { std::string nome;in>>nome;cadastrarItem(nome);std::cout<<"I "<<qtdItens-1<<"\n"; }
    else if(cmd=="H") { std::string nome;in>>nome;cadastrarAventureiro(nome);std::cout<<"H "<<qtdAventureiros-1<<"\n"; }
    else if(cmd=="M") { int i,a,v;in>>i>>a>>v;catalogo.definir(i,a,v);std::cout<<"M "<<itemPorId(i)->getValor().getNome()<<" "<<atributoPorId(a)->getValor().getNome()<<" "<<v<<"\n"; }
    else if(cmd=="F") { int h,i;in>>h>>i;std::cout<<"F "<<fila.enfileirar(h,i)<<"\n"; }
    else if(cmd=="Z") {
        int k;in>>k;Encomenda* feitos=new Encomenda[k];int n=0;Encomenda e;
        while(n<k&&fila.desenfileirar(e)){feitos[n++]=e;aventureiroPorId(e.idAventureiro)->getValor().getBuild().empilhar(e.idItem);}
        std::cout<<"Z "<<n<<"\n";
        if(n){for(int j=0;j<n;j++){if(j)std::cout<<" ";std::cout<<"encomenda_"<<j+1<<" "<<feitos[j].idAventureiro<<" "<<feitos[j].idItem;}std::cout<<"\n";}
        delete[] feitos;
    }
    else if(cmd=="D") { int h,id;in>>h;No<Aventureiro>*p=aventureiroPorId(h);std::string nome="VAZIO";if(p->getValor().getBuild().desempilhar(id))nome=itemPorId(id)->getValor().getNome();std::cout<<"D "<<p->getValor().getNome()<<" "<<nome<<"\n"; }
    else if(cmd=="LI") {
        int id;in>>id;No<Item>*p=itemPorId(id);int n=catalogo.quantidadeLinha(id);
        std::cout<<"LI "<<p->getValor().getNome();
        if(!n) std::cout<<" VAZIO";
        else {Catalogo::Entrada*e=new Catalogo::Entrada[n];catalogo.percorrerLinha(id,e,n);for(int j=0;j<n;j++)std::cout<<" atributo_"<<j+1<<" "<<e[j].id<<" "<<e[j].valor;delete[]e;}
        std::cout<<"\n";
    }
    else if(cmd=="LA") {
        int id;in>>id;No<Atributo>*p=atributoPorId(id);int n=catalogo.quantidadeColuna(id);
        std::cout<<"LA "<<p->getValor().getNome();
        if(!n) std::cout<<" VAZIO";
        else {Catalogo::Entrada*e=new Catalogo::Entrada[n];catalogo.percorrerColuna(id,e,n);for(int j=0;j<n;j++)std::cout<<" item_"<<j+1<<" "<<e[j].id<<" "<<e[j].valor;delete[]e;}
        std::cout<<"\n";
    }
    else if(cmd=="LH" || cmd=="Q") {
        int h;in>>h;No<Aventureiro>*av=aventureiroPorId(h);
        long long* build=new long long[qtdAtributos]();bool* equipado=new bool[qtdItens]();
        Pilha temp;int id;
        while(av->getValor().getBuild().desempilhar(id)){
            temp.empilhar(id);if(cmd=="Q")equipado[id]=true;
            int n=catalogo.quantidadeLinha(id);Catalogo::Entrada*e=new Catalogo::Entrada[n?n:1];
            catalogo.percorrerLinha(id,e,n);for(int j=0;j<n;j++)build[e[j].id]+=e[j].valor;delete[]e;
        }
        while(temp.desempilhar(id))av->getValor().getBuild().empilhar(id);
        if(cmd=="LH") {
            std::cout<<"LH "<<av->getValor().getNome();int count=0;
            for(int a=0;a<qtdAtributos;a++)if(build[a])std::cout<<" atributo_"<<++count<<" "<<a<<" "<<build[a];
            if(!count)std::cout<<" VAZIO";std::cout<<"\n";
        } else {
            int want,m;in>>want>>m;
            long long* pontos=new long long[qtdItens]();
            for(int metrica=0;metrica<m;metrica++) {
                std::string nome,pesoTexto;in>>nome>>pesoTexto;
                double peso;std::istringstream conversorPeso(pesoTexto);conversorPeso>>peso;
                int pesoCentavos=(int)std::floor(peso*100.0+0.5);
                double* valor=new double[qtdItens]();int* ordem=new int[qtdItens];
                for(int i=0;i<qtdItens;i++) {
                    ordem[i]=i;int n=catalogo.quantidadeLinha(i);Catalogo::Entrada*e=new Catalogo::Entrada[n?n:1];catalogo.percorrerLinha(i,e,n);
                    double soma=0,quadrados=0,produto=0;
                    for(int j=0;j<n;j++){soma+=e[j].valor;quadrados+=(double)e[j].valor*e[j].valor;produto+=(double)e[j].valor*build[e[j].id];}
                    if(nome=="PODER")valor[i]=soma;
                    else if(nome=="EQUILIBRIO") {if(!qtdAtributos)valor[i]=1;else{double media=soma/qtdAtributos;double var=quadrados/qtdAtributos-media*media;if(var<0)var=0;valor[i]=1.0/(1.0+std::sqrt(var));}}
                    else {double normaBuild=0;for(int a=0;a<qtdAtributos;a++)normaBuild+=(double)build[a]*build[a];valor[i]=(quadrados>0&&normaBuild>0)?produto/(std::sqrt(quadrados)*std::sqrt(normaBuild)):0;}
                    delete[]e;
                }
                // Selection sort: stable behavior is unnecessary because ties use item id.
                for(int a=0;a<qtdItens;a++)for(int b=a+1;b<qtdItens;b++){
                    double va=std::round(valor[ordem[a]]*1000000.0),vb=std::round(valor[ordem[b]]*1000000.0);
                    if(vb>va||(vb==va&&ordem[b]<ordem[a])){int t=ordem[a];ordem[a]=ordem[b];ordem[b]=t;}
                }
                for(int r=0;r<qtdItens;r++)pontos[ordem[r]]+=(long long)(qtdItens-r)*pesoCentavos;
                delete[]valor;delete[]ordem;
            }
            int* ordemFinal=new int[qtdItens];for(int i=0;i<qtdItens;i++)ordemFinal[i]=i;
            for(int a=0;a<qtdItens;a++)for(int b=a+1;b<qtdItens;b++)if(pontos[ordemFinal[b]]>pontos[ordemFinal[a]]||(pontos[ordemFinal[b]]==pontos[ordemFinal[a]]&&ordemFinal[b]<ordemFinal[a])){int t=ordemFinal[a];ordemFinal[a]=ordemFinal[b];ordemFinal[b]=t;}
            int impressos=0;for(int r=0;r<qtdItens&&impressos<want;r++)if(!equipado[ordemFinal[r]]){std::cout<<"Q "<<++impressos<<" "<<ordemFinal[r]<<" "<<std::fixed<<std::setprecision(2)<<(pontos[ordemFinal[r]]/100.0)<<"\n";}
            std::cout.unsetf(std::ios::floatfield);delete[]pontos;delete[]ordemFinal;
        }
        delete[]build;delete[]equipado;
    }
}

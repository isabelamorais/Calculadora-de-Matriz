#include "Matriz.h"

namespace TP2{

Matriz::Matriz(int qLinha,int qColuna):
    quantidadeDeLinhas(0),
    quantidadeDeColunas(0),
    matriz(0)
{
    if(qLinha<=0) throw QString ("Linha <= 0");
    if(qColuna<=0) throw QString ("Coluna <= 0");

    try{
       matriz = new int[qLinha*qColuna];
    } catch(std::bad_alloc&){
        throw QString("Memoria insuficiente");
    }

    quantidadeDeLinhas = qLinha;
    quantidadeDeColunas = qColuna;

}

Matriz::~Matriz()
{
    if(matriz) delete[] matriz;
}

int Matriz::getElemento(int linha,int coluna)const{
    if(linha<0||linha>=quantidadeDeLinhas)
        throw QString ("Linha fora do intervalo");
    if(coluna<0||coluna>=quantidadeDeColunas)
        throw QString ("Coluna fora do intervalo");

    int posicao = (linha*quantidadeDeColunas)+coluna;

    return *(matriz+posicao);
}

void Matriz::setElemento(int linha, int coluna, int valor)const{
    if(linha<0||linha>=quantidadeDeLinhas)
        throw QString ("Linha fora do intervalo");
    if(coluna<0||coluna>=quantidadeDeColunas)
        throw QString ("Coluna fora do intervalo");

    int posicao = (linha*quantidadeDeColunas)+coluna;

    *(matriz+posicao) = valor;
}

QString Matriz::getConjunto()const{
    QString saida = "";

    for(int linha = 0; linha<getLinhas(); linha++)
    {
        for(int coluna = 0; coluna<getColunas(); coluna++)
        {
            saida+=QString::number(getElemento(linha,coluna));
            saida+=" ";
        }
        saida+="\n";
    }

    return saida;
}

Matriz* Matriz::operator +(Matriz const * const objeto)const{
    if(getLinhas()!=objeto->getLinhas()||getColunas()!=objeto->getColunas())
        throw QString ("Nao e possivel realizar a operacao.\nTamanhos diferentes.");
    try{
    int resultado;

    Matriz* aux = new Matriz (objeto->getLinhas(),objeto->getColunas());

    for(int i=0;i<aux->getLinhas();i++){
        for(int j=0;j<aux->getColunas();j++){
            resultado = getElemento(i,j)+objeto->getElemento(i,j);
            aux->setElemento(i,j,resultado);
        }
    }

    return aux;
    }
    catch(QString &erro){
    throw QString ("Matriz auxiliar nao criada, nao podemos adicionar as matrizes.");
    }
    catch(std::bad_alloc&){
    throw QString ("Matriz nao pode ser criada.");
    }
}

Matriz* Matriz::operator -(Matriz const * const objeto)const{
    if(getLinhas()!=objeto->getLinhas()||getColunas()!=objeto->getColunas())
        throw QString ("Nao e possivel realizar a operacao.\nTamanhos diferentes.");

    try{
    int resultado;

    Matriz* aux = new Matriz (objeto->getLinhas(),objeto->getColunas());

    for(int i=0;i<aux->getLinhas();i++){
        for(int j=0;j<aux->getColunas();j++){
            resultado = getElemento(i,j)-objeto->getElemento(i,j);
            aux->setElemento(i,j,resultado);
        }
    }

    return aux;
    }
    catch(QString &erro){
    throw QString ("Matriz auxiliar nao criada, nao podemos subtrair as matrizes");
    }
    catch(std::bad_alloc&){
    throw QString ("Matriz nao pode ser criada");
    }
}

Matriz* Matriz::operator *(Matriz const * const objeto)const{
    if(getColunas()!=objeto->getLinhas())
        throw QString ("Nao e possivel realizar a operacao");

    try{
    int resultado;

    Matriz* aux = new Matriz (getLinhas(),objeto->getColunas());


    for(int linha = 0; linha < getLinhas(); linha++){
        for(int coluna = 0; coluna < objeto->getColunas(); coluna++){
            resultado = 0;
            for(int i = 0; i < getColunas(); i++){
                resultado+= getElemento(linha,i)*objeto->getElemento(i,coluna);
            }
            aux->setElemento(linha,coluna,resultado);
        }
    }

    return aux;
    }
    catch(QString &erro){
    throw QString ("Matriz auxiliar nao criada.\n\tNao podemos multiplicar as matrizes");
    }
    catch(std::bad_alloc&){
    throw QString ("Matriz nao pode ser criada");
    }
}

bool Matriz::eTriangularInferior()const{
    if(getLinhas()!=getColunas()) return 0;
    if(getLinhas()<=2) return 0;

    int aux=1;

    for(int i=0;i<getColunas()-1;i++){
        for(int j=aux;j<getLinhas();j++){
            if(getElemento(j,i)!=0)
                return 0;
        }
        aux++;
    }
    return 1;
}

bool Matriz::eTriangularSuperior()const{
    if(getLinhas()!=getColunas()) return 0;
    if(getLinhas()<=2) return 0;

    int aux=1;

    for(int j=0;j<getLinhas()-1;j++){
        for(int i=aux;i<getColunas();i++){
            if(getElemento(j,i)!=0)
                return 0;
        }
        aux++;
    }
    return 1;
}

Matriz* Matriz::transposta()const{
    try{

    Matriz* aux = new Matriz (getColunas(),getLinhas());

    for(int i=0;i<aux->getLinhas();i++){
        for(int j=0;j<aux->getColunas();j++){
            aux->setElemento(i,j,getElemento(j,i));
        }
    }

    return aux;
    }
    catch(QString &erro){
    throw QString ("Matriz auxiliar nao criada");
    }
    catch(std::bad_alloc&){
    throw QString ("Matriz nao pode ser criada");
    }
}

bool Matriz::eSimetrica()const{
    return (operator ==(transposta()));
}

bool Matriz::eIdentidade()const{
    if(getLinhas()==getColunas()){
        if(getLinhas()==2)
            return (getElemento(0,1)==0&&getElemento(1,0)==0&&getElemento(0,0)==1&&getElemento(1,1==1));
        else{
            if(getLinhas()<2)
                return 0;
            else{
                if(eTriangularSuperior()&&eTriangularInferior()){
                    for(int j=0;j<getColunas();j++){
                        if(getElemento(j,j)!=1) return 0;
                    }
                    return 1;
                }
                else
                    return 0;
            }
        }
    }
    else
        return 0;
}

Matriz* Matriz::multiplicacaoK(int k)const{
    try{
    Matriz* aux = new Matriz(getLinhas(),getColunas());
    int elemento;

    for(int i=0;i<aux->getLinhas();i++){
        for(int j=0;j<aux->getColunas();j++){
            elemento = k * getElemento(i,j);
            aux->setElemento(i,j,elemento);
        }
    }

    return aux;
    }
    catch(QString &erro){
    throw QString ("Matriz auxiliar nao criada.\n\tNao podemos multiplicar a matriz");
    }
    catch(std::bad_alloc&){
    throw QString ("Matriz nao pode ser criada");
    }
}

Matriz* Matriz::potenciacao(int p)const{
    if(p<0) throw QString("Potencia invalida");
    if(getLinhas()!=getColunas()) throw QString("Matrizes nao quadradas nao podem ser elevadas");
    try{
    int resultado;

    Matriz* aux = new Matriz (getLinhas(),getColunas());

    if(p==0){
        for(int i=0;i<aux->getLinhas();i++){
            for(int j=0;j<aux->getColunas();j++){
                if(i==j)
                    resultado = 1;
                else
                    resultado = 0;
                aux->setElemento(i,j,resultado);
            }
        }
        return aux;
    }

    for(int i=0;i<aux->getLinhas();i++){
        for(int j=0;j<aux->getColunas();j++){
            resultado = getElemento(i,j);
            aux->setElemento(i,j,resultado);
        }
    }

    if(p==1)
        return aux;

    for(int i=2;i<=p;i++){
        Matriz* temp = aux;
        aux=operator *(aux);
        delete temp;
    }

    return aux;
    }
    catch(QString &erro){
    throw QString ("Matriz auxiliar nao criada");
    }
    catch(std::bad_alloc&){
    throw QString ("Matriz nao pode ser criada");
    }
}

bool Matriz::eMatrizDePermutacao()const{
    if(getLinhas()!=getColunas()) return 0;
    if(getLinhas()==1&&getElemento(0,0)==1) return 1;

    int k;

    for(int i=0;i<getLinhas();i++){
        k=0;
        for(int j=0;j<getColunas();j++){
            if(getElemento(i,j)>=0&&getElemento(i,j)<=1){
                if(getElemento(i,j)==1)
                    k++;
            }
            else
                return 0;
        }
        if(k!=1)
            return 0;
    }

    return 1;
}

bool Matriz::eMatrizOrtogonal()const{
    return(operator *(transposta())->eIdentidade());
}

}

#ifndef MATRIZ_H
#define MATRIZ_H
#include<QString>

//posicao = (linha * numero de colunas) + coluna

namespace TP2 {

class Matriz
{
private:
    int *matriz;
    int quantidadeDeLinhas;
    int quantidadeDeColunas;
public:
    Matriz(int qLinha, int qColuna);
    ~Matriz();
    int getLinhas()const{return quantidadeDeLinhas;}
    int getColunas()const{return quantidadeDeColunas;}
    int getElemento(int linha, int coluna)const;
    void setElemento(int linha, int coluna, int valor)const;
    Matriz* operator +(Matriz const * const objeto)const;
    Matriz* operator -(Matriz const * const objeto)const;
    Matriz* operator *(Matriz const * const objeto)const;
    bool operator ==(Matriz const * const objeto)const{return (getLinhas()==objeto->getLinhas()&&getColunas()==objeto->getColunas()&&getConjunto()==objeto->getConjunto());}
    bool operator !=(Matriz const * const objeto)const{return (getColunas()!=objeto->getColunas()||getLinhas()!=objeto->getLinhas()||getConjunto()!=objeto->getConjunto());}
    bool eTriangularSuperior()const;
    bool eTriangularInferior()const;
    Matriz* transposta()const;
    bool eSimetrica()const;
    bool eIdentidade()const;
    Matriz* multiplicacaoK(int k)const;
    Matriz* potenciacao(int p)const;
    bool eMatrizDePermutacao()const;
    bool eMatrizOrtogonal()const;
    QString getConjunto()const;
};

}

#endif // MATRIZ_H

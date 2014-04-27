#ifndef CIRCUITO_H
#define CIRCUITO_H

#include <fstream>
#include <vector>
#include <string>
#include <QTextStream>
#include <QString>
#include <armadillo>
#include "complexo.h"
#include "elementos.h"

using namespace arma;
using namespace std;

class Circuito
{
    private:
        ofstream fout;
        QTextStream* out;
        vector<Elemento*> listaElementos;
        //Quantidade de pontos (frequências) a simular, e frequências inicial e final
        int pontos;
        double inicio, fim;
        string tipo;
        //G*e = b
        Complexo **G; // <---------------------------------------------
        //Lista de nomes das incógnitas
        vector<string> listaInc;
        vector<string> listaNo;
        Complexo *e, *b; // <------------------------------------
        int adicionaNo(string);
        int adicionaInc(string);
        void leNetlist(char*);
        void leNetlistQT(QString);
        void montaMatriz(double, string);
        void resolveSistema();

    public:
        Circuito(char*);
        Circuito(QString);
};

#endif // CIRCUITO_H

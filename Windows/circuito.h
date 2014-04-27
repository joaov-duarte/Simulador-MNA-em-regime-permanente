#ifndef CIRCUITO_H
#define CIRCUITO_H

#include <fstream>
#include <vector>
#include <string>
#include <QTextStream>
#include <QString>
#include "elementos.h"

class Circuito
{
    private:
        std::ofstream fout;
        QTextStream* out;
        std::vector<Elemento*> listaElementos;
        //Quantidade de pontos (frequências) a simular, e frequências inicial e final
        int pontos;
        double inicio, fim;
        std::string tipo;
        //G*e = b
        Complexo** G;
        //Lista de nomes das incógnitas
        std::vector<std::string> listaInc;
        std::vector<std::string> listaNo;
        Complexo *e, *b;
        int adicionaNo(std::string);
        int adicionaInc(std::string);
        void leNetlist(char*);
        void leNetlistQT(QString);
        void montaMatriz(double, std::string);
        void resolveSistema();

    public:
        Circuito(char*);
        Circuito(QString);
};

#endif // CIRCUITO_H

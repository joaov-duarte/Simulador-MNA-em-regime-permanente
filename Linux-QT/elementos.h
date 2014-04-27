#ifndef ELEMENTOS_H
#define ELEMENTOS_H

#include <string>
#include "complexo.h"

class Elemento
{
    protected:
        std::string nome;
        int noa, nob;
    public:
        int getNoa();
        void setNoa(int);
        int getNob();
        void setNob(int);
        std::string getNome();
        void setNome(std::string);
        virtual void somaEstampa(double, Complexo**, Complexo*) = 0;
};

class Resistor : public Elemento
{
    protected:
        double resistencia;
    public:
        Resistor(std::string, int, int, double);
        void somaEstampa(double, Complexo**, Complexo*);
};

class Capacitor : public Elemento
{
    protected:
        double capacitancia;
    public:
        Capacitor();
        Capacitor(std::string, int, int, double);
        double getCapacitancia();
        void setCapacitancia(double);
        void somaEstampa(double, Complexo**, Complexo*);
};

class Indutor : public Elemento
{
    protected:
        double indutancia;
        int ijx;
    public:
        Indutor(std::string, int, int, int, double);
        int getIjx();
        void setIjx(int);
        double getIndutancia();
        void setIndutancia(double);
        void somaEstampa(double, Complexo**, Complexo*);
};

class IndutanciaMutua : public Elemento
{
    protected:
        double k;
        Indutor *l1, *l2;
    public:
        IndutanciaMutua(std::string, Indutor*, Indutor*, double);
        void somaEstampa(double, Complexo**, Complexo*);
};

class FonteTensao : public Elemento
{
    protected:
        double modulo, fase;
        int ijx;
    public:
        FonteTensao(std::string, int, int, int, double);
        FonteTensao(std::string, int, int, int, double, double);
        void somaEstampa(double, Complexo**, Complexo*);
};

class FonteCorrente : public Elemento
{
    protected:
        double modulo, fase;
    public:
        FonteCorrente(std::string, int, int, double);
        FonteCorrente(std::string, int, int, double, double);
        void somaEstampa(double, Complexo**, Complexo*);
};

class Transcondutor : public Elemento
{
    protected:
        double gm;
        int noc, nod;
    public:
        Transcondutor(std::string, int, int, int, int, double);
        void somaEstampa(double, Complexo**, Complexo*);
};

class Transresistor : public Elemento
{
    protected:
        double rm;
        int noc, nod, ijx, ijy;
    public:
        Transresistor(std::string, int, int, int, int, int, int, double);
        void somaEstampa(double, Complexo**, Complexo*);
};

class AmpDeTensao : public Elemento
{
    protected:
        double av;
        int noc, nod, ijx;
    public:
        AmpDeTensao(std::string, int, int, int, int, int, double);
        void somaEstampa(double, Complexo**, Complexo*);
};

class AmpDeCorrente : public Elemento
{
    protected:
        double ai;
        int noc, nod, ijx;
    public:
        AmpDeCorrente(std::string, int, int, int, int, int, double);
        void somaEstampa(double, Complexo**, Complexo*);
};

class AmpOp : public Elemento
{
    protected:
        int noc, nod, ijx;
    public:
        AmpOp(std::string, int, int, int, int, int);
        void somaEstampa(double, Complexo**, Complexo*);
};

class TransBipolar : public Elemento
{
    protected:
        int noc, iib;
        double hfe, hie, hre, hoe;
        Capacitor cbc, cbe;
    public:
        TransBipolar(std::string, int, int, int, int, double, double, double, double);
        TransBipolar(std::string, int, int, int, int, double, double, double, double, double, double);
        void somaEstampa(double, Complexo**, Complexo*);
};

#endif // ELEMENTOS_H

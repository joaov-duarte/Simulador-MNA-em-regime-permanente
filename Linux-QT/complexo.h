#ifndef COMPLEXO_H
#define COMPLEXO_H

class Complexo
{
private:
    double a, b;
public:
    Complexo();
    Complexo(double, double);
    Complexo(double, double, char);
    double getA();
    void setA(double);
    double getB();
    void setB(double);
    void setAB(double , double);
    double calculaModulo();
    double calculaFase();
    Complexo operator+(Complexo);
    Complexo operator-(Complexo);
    Complexo operator*(Complexo);
    Complexo operator/(Complexo);
    Complexo operator=(Complexo);
    Complexo operator=(double);
    Complexo operator+=(Complexo);
    Complexo operator+=(double);
    Complexo operator-=(Complexo);
    Complexo operator-=(double);
};

#endif // COMPLEXO_H

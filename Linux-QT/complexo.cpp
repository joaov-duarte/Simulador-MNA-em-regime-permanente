#include "complexo.h"
#include <cmath>

Complexo::Complexo()
{
}

Complexo::Complexo(double a, double b)
{
    this->a = a;
    this->b = b;
}

Complexo::Complexo(double modulo, double fase, char tipo)
{
    //Graus
    if (tipo == 'g')
    {
        this->a = cos(fase * M_PI / 180) * modulo;
        this->b = sin(fase * M_PI / 180) * modulo;
    }
    //Radianos
    else if (tipo == 'r')
    {
        this->a = cos(fase) * modulo;
        this->a = sin(fase) * modulo;
    }
}

double Complexo::getA()
{
    return this->a;
}

void Complexo::setA(double a)
{
    this->a = a;
}

double Complexo::getB()
{
    return this->b;
}

void Complexo::setB(double b)
{
    this->b = b;
}

void Complexo::setAB(double a, double b)
{
    this->a = a;
    this->b = b;
}

double Complexo::calculaModulo()
{
    return sqrt(a * a + b * b);
}

double Complexo::calculaFase()
{
    double aux = calculaModulo();
    if (aux != 0)
    {
        if (a >= 0)
            aux = asin(b / aux);
        else if (b >= 0)
            aux = M_PI + asin(-b / aux);
        else
            aux = asin(-b / aux) - M_PI;
    }
    return aux;
}

Complexo Complexo::operator+(Complexo z)
{
    Complexo aux;
    aux.setA(this->a + z.getA());
    aux.setB(this->b + z.getB());
    return aux;
}

Complexo Complexo::operator-(Complexo z)
{
    Complexo aux;
    aux.setA(this->a - z.getA());
    aux.setB(this->b - z.getB());
    return aux;
}

Complexo Complexo::operator*(Complexo z)
{
    Complexo aux;
    aux.setA(this->a * z.getA() - this->b * z.getB());
    aux.setB(this->a * z.getB() + this->b * z.getA());
    return aux;
}

Complexo Complexo::operator/(Complexo z)
{
    Complexo aux;
    if (std::abs(z.getA()) > std::abs(z.getB()))
    {
        aux.setA( (a + b * (z.getB() / z.getA())) / (z.getA() + z.getB() * (z.getB() / z.getA())) );
        aux.setB( (b - a * (z.getB() / z.getA())) / (z.getA() + z.getB() * (z.getB() / z.getA())) );
    }
    else
    {
        aux.setA( (b + a * (z.getA() / z.getB())) / (z.getB() + z.getA() * (z.getA() / z.getB())) );
        aux.setB( (-a + b * (z.getA() / z.getB())) / (z.getB() + z.getA() * (z.getA() / z.getB())) );
    }
    return aux;
}

Complexo Complexo::operator=(Complexo z)
{
    a = z.getA();
    b = z.getB();
    return *this;
}

Complexo Complexo::operator=(double a)
{
    this->a = a;
    this->b = 0;
    return *this;
}

Complexo Complexo::operator+=(Complexo z)
{
    a = a + z.getA();
    b = b + z.getB();
    return *this;
}

Complexo Complexo::operator+=(double a)
{
    this->a = this->a + a;
    return *this;
}

Complexo Complexo::operator-=(Complexo z)
{
    a = a - z.getA();
    b = b - z.getB();
    return *this;
}

Complexo Complexo::operator-=(double a)
{
    this->a = this->a - a;
    return *this;
}

/*int main ()
{
    Complexo* z1 = new Complexo(0,0);
    Complexo* z2 = new Complexo(5,0);
    Complexo z3 = (*z1)/(*z2);
    Complexo z4(1,45,'a');
    printf("z3 = %.15f + %.15fi \n", z3.getA(), z3.getB());
    printf("z3 = %.15f /_%.15f \n", z3.calculaModulo(), z3.calculaFase());
    printf("z4 = %.15f + %.15fi \n", z4.getA(), z4.getB());
    printf("z4 = %.15f /_%.15f \n", z4.calculaModulo(), z4.calculaFase());
    getchar();
    delete(z1);
    delete(z2);
    return 0;
}*/

#include "complexo.h"

Complexo::Complexo()
{
}

Complexo::Complexo(double real, double imag)
{
	rr = real;
	ii = imag;
}

Complexo::Complexo(double modulo, double fase, char tipo)
{
	rr = cos(fase * M_PI / 180) * modulo;
	ii = sin(fase * M_PI / 180) * modulo;
}

double Complexo::real()
{
	return rr;
}

double Complexo::imag()
{
	return ii;
}

void Complexo::setReal(double a)
{
	rr = a;
}

void Complexo::setImag(double b)
{
	ii = b;
}

void Complexo::setComplex(double a, double b)
{
	rr = a;
	ii = b;
}

double Complexo::modulo()
{
	return sqrt(rr * rr + ii * ii);
}

double Complexo::fase()
{
	double aux = modulo();
	if (aux != 0)
	{
		if (rr >= 0)
			aux = asin(ii / aux);
		else
			aux = M_PI + asin(ii / aux);
	}
	return aux;
}

Complexo Complexo::operator+(Complexo z)
{
	Complexo aux;
	aux.setReal(rr + z.real());
	aux.setImag(ii + z.imag());
	return aux;
}

Complexo Complexo::operator-(Complexo z)
{
	Complexo aux;
	aux.setReal(rr - z.real());
	aux.setImag(ii - z.imag());
	return aux;
}

Complexo Complexo::operator*(Complexo z)
{
	Complexo aux;
	aux.setReal(rr * z.real() - ii * z.imag());
	aux.setImag(rr * z.imag() + ii * z.real());
	return aux;
}

Complexo Complexo::operator/(Complexo z)
{
	Complexo aux;
	double r2 = z.real() * z.real() + z.imag() * z.imag();
	aux.setReal( (rr * z.real() + ii * z.imag()) / r2);
	aux.setImag( (-rr * z.imag() + ii * z.real()) / r2);
	return aux;
}

Complexo Complexo::operator=(Complexo z)
{
	rr = z.real();
	ii = z.imag();
	return *this;
}

Complexo Complexo::operator=(double a)
{
	rr = a;
	ii = 0;
	return *this;
}

Complexo Complexo::operator+=(Complexo z)
{
	rr = rr + z.real();
	ii = ii + z.imag();
	return *this;
}

Complexo Complexo::operator-=(Complexo z)
{
	rr = rr - z.real();
	ii = ii - z.imag();
	return *this;
}

int main ()
{
	Complexo* z1 = new Complexo(4,15);
	Complexo* z2 = new Complexo(5,8);
	Complexo z3 = (*z1)/(*z2);
	Complexo z4(1,45,'a');
	printf("z3 = %.15f + %.15fi \n", z3.real(), z3.imag());
	printf("z3 = %.15f /_%.15f \n", z3.modulo(), z3.fase());
	printf("z4 = %.15f + %.15fi \n", z4.real(), z4.imag());
	printf("z4 = %.15f /_%.15f \n", z4.modulo(), z4.fase());
	getchar();
	delete(z1);
	delete(z2);
	return 0;
}

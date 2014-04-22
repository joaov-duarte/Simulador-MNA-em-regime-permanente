#define _USE_MATH_DEFINES
#include <math.h>
#include "stdio.h"

class Complexo
{
	private:
		double rr, ii;
		
	public:
		//contructor
		Complexo();
		
		//Overload
		Complexo(double real, double imag);                //a + bi
		Complexo(double modulo, double fase, char tipo);   //modulo, fase e não faço a minima ideia do que seja o tipo
		
		//Valores
		double real();
		double imag();
		
		//Set nos valores
		void setReal(double);
		void setImag(double);
		void setComplex(double real, double imag);
		
		//Funções
		double modulo();
		double fase();
		
		//Operadores
		Complexo operator+(Complexo);
		Complexo operator-(Complexo);
		Complexo operator*(Complexo);
		Complexo operator/(Complexo);
		Complexo operator=(Complexo);
		Complexo operator=(double);
		Complexo operator+=(Complexo);
		Complexo operator-=(Complexo);
};

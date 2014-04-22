#include <string>
#include "complexo.h"

class Elemento
{
	protected:
		std::string nome;
		int* no;
	public:
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
		Capacitor(std::string, int, int, double);
		void somaEstampa(double, Complexo**, Complexo*);
};

class Indutor : public Elemento
{
	protected:
		double indutancia;
	public:
		Indutor(std::string, int, int, double);
		void somaEstampa(double, Complexo**, Complexo*);
};

class FonteTensao : public Elemento
{
	protected:
		double modulo, fase;
		int ijx;
	public:
		FonteTensao(std::string, int, int, int, double, double);
		void somaEstampa(double, Complexo**, Complexo*);
};

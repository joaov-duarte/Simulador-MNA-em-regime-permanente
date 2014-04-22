#include "elementos.h"

//Resistor
Resistor::Resistor(std::string nome, int no1, int no2, double resistencia)
{
	this->nome = nome;
	this->no[0] = no1;
	this->no[1] = no2;
	this->resistencia = resistencia;
}

void Resistor::somaEstampa(double w, Complexo** m, Complexo* b)
{
	std::string teste;
	Complexo g(1/resistencia, 0);
	if(no[0] >= 0 && no[1] >= 0)
	{
		m[no[0]][no[0]] += g;
		m[no[1]][no[1]] += g;
		m[no[0]][no[1]] -= g;
		m[no[1]][no[0]] -= g;
	}
	else if(no[0] >= 0)
		m[no[0]][no[0]] += g;
	else if(no[1] >= 0)
		m[no[1]][no[1]] += g;
}

//Capacitor
Capacitor::Capacitor(std::string nome, int no1, int no2, double resistencia)
{
	this->nome = nome;
	this->no[0] = no1;
	this->no[1] = no2;
	this->capacitancia = capacitancia;
}

void Capacitor::somaEstampa(double w, Complexo** m, Complexo* b)
{
	Complexo g(0, w*capacitancia);
	if(no[0] >= 0 && no[1] >= 0)
	{
		m[no[0]][no[0]] += g;
		m[no[1]][no[1]] += g;
		m[no[0]][no[1]] -= g;
		m[no[1]][no[0]] -= g;
	}
	else if(no[0] >= 0)
		m[no[0]][no[0]] += g;
	else if(no[1] >= 0)
		m[no[1]][no[1]] += g;
}

//Indutor
Indutor::Indutor(std::string nome, int no1, int no2, double resistencia)
{
	this->nome = nome;
	this->no[0] = no1;
	this->no[1] = no2;
	this->indutancia = indutancia;
}

void Indutor::somaEstampa(double w, Complexo** m, Complexo* b)
{
	Complexo g(0, 1/(w*indutancia));
	if(no[0] >= 0 && no[1] >= 0)
	{
		m[no[0]][no[0]] += g;
		m[no[1]][no[1]] += g;
		m[no[0]][no[1]] -= g;
		m[no[1]][no[0]] -= g;
	}
	else if(no[0] >= 0)
		m[no[0]][no[0]] += g;
	else if(no[1] >= 0)
		m[no[1]][no[1]] += g;
}

//Fonte de Tensão
FonteTensao::FonteTensao(std::string nome, int no1, int no2, int ijx, double modulo, double fase)
{
	this->nome = nome;
	this->no[0] = no1;
	this->no[1] = no2;
	this->ijx = ijx;
	this->modulo = modulo;
	this->fase = fase;
}

void FonteTensao::somaEstampa(double w, Complexo** m, Complexo* b)
{
	//Complexo g(0, 1/(w*indutancia));
	//m[no[0]][no[0]] += g;
	//m[no[1]][no[1]] += g;
	//m[no[0]][no[1]] -= g;
	//m[no[1]][no[0]] -= g;
}

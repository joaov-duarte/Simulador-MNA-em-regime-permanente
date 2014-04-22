#include <fstream>
#include <vector>
#include <string>
#include "elementos.h"

class Circuito
{
	private:
		std::vector<Elemento*> listaElementos;
		//Quantidade de pontos (frequências) a simular, e frequências inicial e final
		int pontos;
		double inicio, fim;
		std::string tipo;
		//G*e = b
		Complexo** G;
		//Lista de nomes das incógnitas
		std::vector<std::string> listaInc;
		Complexo *e, *b;
		//Quantidade de nós
		int nNos;
		int adicionaNo(std::string);
		
		//std::string* separaString(std::string, int);
		//double stod(std::string);
		//int stoi(std::string);
		//Elemento* trataLinha(std::string);
	public:
		Circuito(char*);
};

#include <fstream>
#include <vector>
#include <string>
#include "elementos.h"

class Circuito
{
	private:
		std::vector<Elemento*> listaElementos;
		//Quantidade de pontos (frequ�ncias) a simular, e frequ�ncias inicial e final
		int pontos;
		double inicio, fim;
		std::string tipo;
		//G*e = b
		Complexo** G;
		//Lista de nomes das inc�gnitas
		std::vector<std::string> listaInc;
		Complexo *e, *b;
		//Quantidade de n�s
		int nNos;
		int adicionaNo(std::string);
		
		//std::string* separaString(std::string, int);
		//double stod(std::string);
		//int stoi(std::string);
		//Elemento* trataLinha(std::string);
	public:
		Circuito(char*);
};

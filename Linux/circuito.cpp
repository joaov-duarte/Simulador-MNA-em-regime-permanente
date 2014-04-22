#include "circuito.h"

Circuito::Circuito(char* nomeArquivo)
{
	//nNos = 0;
	//ne = 0;
	std::ifstream fin(nomeArquivo);
	std::string nome;
	std::string no[4];
	double valor[4];
	if (fin.is_open())
  	{
		getline(fin, nome); //pula primeira linha
		Elemento* elemento;
		while(/*(getline(fin, linha)*/ fin >> nome)
		{
			//aux = trataLinha(linha);
			//if (aux)
			//	this->listaElementos.push_back(aux);
			switch (nome[0])
			{
				case 'R':
					//param = separaString(linha, 4);
					fin >> no[0] >> no[1] >> valor[0];
					elemento = new Resistor(nome, adicionaNo(no[0]), adicionaNo(no[1]), valor[0]);
					break;
				case 'L':
					//param = separaString(linha, 4);
					fin >> no[0] >> no[1] >> valor[0];
					elemento = new Indutor(nome, adicionaNo(no[0]), adicionaNo(no[1]), valor[0]);
					break;
				case 'K':
					break;
				case 'C':
					//param = separaString(linha, 4);
					fin >> no[0] >> no[1] >> valor[0];
					elemento = new Capacitor(nome, adicionaNo(no[0]), adicionaNo(no[1]), valor[0]);
					break;
				case 'E':
					break;
				case 'F':
					break;
				case 'G':
					break;
				case 'H':
					break;
				case 'I':
					break;
				case 'V':
					fin >> no[0] >> no[1] >> valor[0] >> valor[1];
					elemento = new FonteTensao(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaNo("j" + nome), valor[0], valor[1]);
					break;
				case 'O':
					break;
				case 'Q':
					break;
			}
		}
	}
	e = new Complexo[listaInc.size() - 1];
	b = new Complexo[listaInc.size() - 1];
	G = new Complexo*[listaInc.size() - 1];
	for (int i = 0; i < listaInc.size() - 1; i++)
	{
		G[i] = new Complexo[listaInc.size() - 1];
		e[i] = 0;
		b[i] = 0;
		for (int j = 0; j < listaInc.size() - 1; i++)
		{
			G[i][j] = 0;
		}
	}
}

int Circuito::adicionaNo(std::string nome)
{
	if (nome == "0")
		return -1;
	int i;
	for(i = 0; i < listaInc.size(); i++)
		if(listaInc[i] == nome)
			return i;
	//nNos++;
	listaInc.push_back(nome);
	return i;
}

/*Elemento* Circuito::trataLinha(std::string linha)
{
		Elemento* elemento = 0;
		std::string* param;
		switch (linha[0])
		{
			case 'R':
				param = separaString(linha, 4);
				elemento = new Resistor(param[0], std::stoi(param[1]), std::stoi(param[2]), std::stod(param[3]));
				break;
			case 'L':
				param = separaString(linha, 4);
				elemento = new Indutor(param[0], std::stoi(param[1]), std::stoi(param[2]), std::stod(param[3]));
				break;
			case 'K':
				break;
			case 'C':
				param = separaString(linha, 4);
				elemento = new Capacitor(param[0], std::stoi(param[1]), std::stoi(param[2]), std::stod(param[3]));
				break;
			case 'E':
				break;
			case 'F':
				break;
			case 'G':
				break;
			case 'H':
				break;
			case 'I':
				break;
			case 'V':
				break;
			case 'O':
				break;
			case 'Q':
				break;
		}
		return elemento;
}

std::string* Circuito::separaString(std::string linha, int n)
{
	std::string* s = new std::string[n];
	std::size_t inicio, fim;
	inicio = 0;
	for (int i = 0; i < n; i++)
	{
		fim = linha.find(' ', inicio);
		if (fim != std::string::npos)
		{
			s[i] = linha.substr(inicio, fim - inicio);
			inicio = fim + 1;
		}
		else
			s[i] = linha.substr(inicio, linha.length() - inicio);
	}
	return s;
}*/

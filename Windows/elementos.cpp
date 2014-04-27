#include "elementos.h"
#include <cmath>
#include <QDebug>
//Elemento genérico
int Elemento::getNoa()
{
    return this->noa;
}

void Elemento::setNoa(int noa)
{
    this->noa = noa;

}
int Elemento::getNob()
{
    return this->nob;
}

void Elemento::setNob(int nob)
{
    this->nob = nob;
}

std::string Elemento::getNome()
{
    return this->nome;
}

void Elemento::setNome(std::string nome)
{
    this->nome = nome;
}

//Resistor
Resistor::Resistor(std::string nome, int noa, int nob, double resistencia)
{
    this->nome = nome;
    this->noa = noa;
    this->nob = nob;
    this->resistencia = resistencia;
}

void Resistor::somaEstampa(double, Complexo** m, Complexo*)
{
    double g = 1/resistencia;
    m[noa][noa] += g;
    m[nob][nob] += g;
    m[noa][nob] -= g;
    m[nob][noa] -= g;
}

//Capacitor
Capacitor::Capacitor()
{
}

Capacitor::Capacitor(std::string nome, int noa, int nob, double capacitancia)
{
    this->nome = nome;
    this->noa = noa;
    this->nob = nob;
    this->capacitancia = capacitancia;
}

double Capacitor::getCapacitancia()
{
    return this->capacitancia;
}

void Capacitor::setCapacitancia(double capacitancia)
{
    this->capacitancia = capacitancia;
}

void Capacitor::somaEstampa(double w, Complexo** m, Complexo*)
{
    Complexo g(0, w*capacitancia);
    m[noa][noa] += g;
    m[nob][nob] += g;
    m[noa][nob] -= g;
    m[nob][noa] -= g;
}

//Indutor
Indutor::Indutor(std::string nome, int noa, int nob, int ijx, double indutancia)
{
    this->nome = nome;
    this->noa = noa;
    this->nob = nob;
    this->ijx = ijx;
    this->indutancia = indutancia;
}

double Indutor::getIndutancia()
{
    return this->indutancia;
}

void Indutor::setIndutancia(double indutancia)
{
    this->indutancia = indutancia;
}

int Indutor::getIjx()
{
    return this->ijx;
}

void Indutor::setIjx(int ijx)
{
    this->ijx = ijx;
}

void Indutor::somaEstampa(double w, Complexo** m, Complexo*)
{
    Complexo z(0, w*indutancia);
    m[noa][ijx] += 1;
    m[nob][ijx] -= 1;
    m[ijx][noa] -= 1;
    m[ijx][nob] += 1;
    m[ijx][ijx] += z;
}

//Indutância Mútua
IndutanciaMutua::IndutanciaMutua(std::string nome, Indutor* l1, Indutor* l2, double k)
{
    this->nome = nome;
    this->l1 = l1;
    this->l2 = l2;
    this->k = k;
}

void IndutanciaMutua::somaEstampa(double w, Complexo** m, Complexo*)
{
    Complexo aux(0, w * k * sqrt(l1->getIndutancia() * l2->getIndutancia())); // jwM
    m[l1->getIjx()][l2->getIjx()] += aux;
    m[l2->getIjx()][l1->getIjx()] += aux;
}

//Fonte de Tensão
FonteTensao::FonteTensao(std::string nome, int noa, int nob, int ijx, double modulo)
{
    this->nome = nome;
    this->noa = noa;
    this->nob = nob;
    this->ijx = ijx;
    this->modulo = modulo;
    this->fase = 0;
}

FonteTensao::FonteTensao(std::string nome, int noa, int nob, int ijx, double modulo, double fase)
{
    this->nome = nome;
    this->noa = noa;
    this->nob = nob;
    this->ijx = ijx;
    this->modulo = modulo;
    this->fase = fase;
}

void FonteTensao::somaEstampa(double, Complexo** m, Complexo* b)
{
    Complexo v(modulo, fase, 'g');
    b[ijx] += v;
    m[noa][ijx] += 1;
    m[nob][ijx] -= 1;
    m[ijx][noa] += 1;
    m[ijx][nob] -= 1;
}

//Fonte de Corrente
FonteCorrente::FonteCorrente(std::string nome, int noa, int nob, double modulo)
{
    this->nome = nome;
    this->noa = noa;
    this->nob = nob;
    this->modulo = modulo;
    this->fase = 0.0;
}

FonteCorrente::FonteCorrente(std::string nome, int noa, int nob, double modulo, double fase)
{
    this->nome = nome;
    this->noa = noa;
    this->nob = nob;
    this->modulo = modulo;
    this->fase = fase;
}

void FonteCorrente::somaEstampa(double, Complexo**, Complexo* b)
{
    Complexo I(modulo, fase, 'g');
    b[noa] -= I;
    b[nob] += I;
}

//Transcondutor
Transcondutor::Transcondutor(std::string nome, int noa, int nob, int noc, int nod, double gm)
{
    this->nome = nome;
    this->noa = noa;
    this->nob = nob;
    this->noc = noc;
    this->nod = nod;
    this->gm = gm;
}

void Transcondutor::somaEstampa(double, Complexo** m, Complexo*)
{
    m[noa][noc] += gm;
    m[nob][nod] += gm;
    m[noa][nod] -= gm;
    m[nob][noc] -= gm;
}

//Transresistor
Transresistor::Transresistor(std::string nome, int noa, int nob, int noc, int nod, int ijx, int ijy, double rm)
{
    this->nome = nome;
    this->noa = noa;
    this->nob = nob;
    this->noc = noc;
    this->nod = nod;
    this->ijx = ijx;
    this->ijy = ijy;
    this->rm = rm;
}

void Transresistor::somaEstampa(double, Complexo** m, Complexo*)
{
    m[noa][ijx] += 1;
    m[nob][ijx] -= 1;
    m[noc][ijy] += 1;
    m[nod][ijy] -= 1;
    m[ijx][noa] -= 1;
    m[ijx][nob] += 1;
    m[ijy][noc] -= 1;
    m[ijy][nod] += 1;
    m[ijx][ijy] += rm;
}

//Amplificador de Tensão
AmpDeTensao::AmpDeTensao(std::string nome, int noa, int nob, int noc, int nod, int ijx, double av)
{
    this->nome = nome;
    this->noa = noa;
    this->nob = nob;
    this->noc = noc;
    this->nod = nod;
    this->ijx = ijx;
    this->av = av;
}

void AmpDeTensao::somaEstampa(double, Complexo** m, Complexo*)
{
    m[noa][ijx] += 1;
    m[nob][ijx] -= 1;
    m[ijx][noa] -= 1;
    m[ijx][nob] += 1;
    m[ijx][noc] += av;
    m[ijx][nod] -= av;
}

//Amplificador de Corrente
AmpDeCorrente::AmpDeCorrente(std::string nome, int noa, int nob, int noc, int nod, int ijx, double ai)
{
    this->nome = nome;
    this->noa = noa;
    this->nob = nob;
    this->noc = noc;
    this->nod = nod;
    this->ijx = ijx;
    this->ai = ai;
}

void AmpDeCorrente::somaEstampa(double, Complexo** m, Complexo*)
{
    m[noa][ijx] += ai;
    m[nob][ijx] -= ai;
    m[noc][ijx] += 1;
    m[nod][ijx] -= 1;
    m[ijx][noc] += 1;
    m[ijx][nod] -= 1;
}

//Amplificador Operacional
AmpOp::AmpOp(std::string nome, int noa, int nob, int noc, int nod, int ijx)
{
    this->nome = nome;
    this->noa = noa;
    this->nob = nob;
    this->noc = noc;
    this->nod = nod;
    this->ijx = ijx;
}

void AmpOp::somaEstampa(double, Complexo** m, Complexo*)
{
    m[noa][ijx] += 1;
    m[nob][ijx] -= 1;
    m[ijx][noc] += 1;
    m[ijx][nod] -= 1;
}

//Transistor bipolar
TransBipolar::TransBipolar(std::string nome, int coletor, int base, int emissor, int iib, double hfe, double hie, double hre, double hoe)
{
    this->nome = nome;
    this->noa = coletor;
    this->nob = base;
    this->noc = emissor;
    this->iib = iib;
    this->hfe = hfe;
    this->hie = hie;
    this->hre = hre;
    this->hoe = hoe;
    this->cbe.setNoa(base);
    this->cbe.setNob(emissor);
    this->cbe.setCapacitancia(0.0);
    this->cbc.setNoa(base);
    this->cbc.setNob(coletor);
    this->cbc.setCapacitancia(0.0);
}

TransBipolar::TransBipolar(std::string nome, int coletor, int base, int emissor, int iib, double hfe, double hie, double hre, double hoe, double cbe, double cbc)
{
    this->nome = nome;
    this->noa = coletor;
    this->nob = base;
    this->noc = emissor;
    this->iib = iib;
    this->hfe = hfe;
    this->hie = hie;
    this->hre = hre;
    this->hoe = hoe;
    this->cbe.setNoa(base);
    this->cbe.setNob(emissor);
    this->cbe.setCapacitancia(cbe);
    this->cbc.setNoa(base);
    this->cbc.setNob(coletor);
    this->cbc.setCapacitancia(cbc);
}

void TransBipolar::somaEstampa(double w, Complexo** m, Complexo* b)
{
    m[nob][iib] += 1;
    m[noa][noa] += hoe;
    m[noa][noc] -= hoe;
    m[noa][iib] += hfe;
    m[noc][noa] -= hoe;
    m[noc][noc] += hoe;
    m[noc][iib] -= 1 + hfe;
    m[iib][noa] -= hre / hie;
    m[iib][nob] += 1 / hie;
    m[iib][noc] += (hre - 1) / hie;
    m[iib][iib] -= 1;
    cbe.somaEstampa(w, m, b);
    cbc.somaEstampa(w, m, b);
}

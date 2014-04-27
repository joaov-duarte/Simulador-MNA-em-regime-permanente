#include "circuito.h"
#include <cmath>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>

Circuito::Circuito(QString nomeArquivo)
{
    int i;
    double wlog, w, intervalo;
    tipo = "LIN";
    inicio = 1;
    fim = 10000;
    pontos = 1000;
    listaInc.push_back("0");
    listaNo.push_back("0");
    leNetlistQT(nomeArquivo);
    e = new Complexo[listaInc.size()];
    b = new Complexo[listaInc.size()];
    G = new Complexo*[listaInc.size()];
    QFileInfo info(nomeArquivo);
    nomeArquivo = info.baseName();
    nomeArquivo += ".tab";
    QFile arquivoTabela(nomeArquivo);
    if (!arquivoTabela.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    out = new QTextStream(&arquivoTabela);
    *out<< "f";
    for (i = 0; i < listaInc.size(); i++)
    {
        G[i] = new Complexo[listaInc.size()];
        if (i!=0)
            *out << " " << (listaInc[i] + "m").c_str() << " " << (listaInc[i] + "f").c_str();
    }

    intervalo = 1.0 / pontos;
    *out << "teste";
    qDebug() << "Tipo:" << tipo.c_str();
    if (tipo == "OCT")
    {
        inicio = log2(inicio);
        fim = log2(fim);
    }
    else if (tipo == "DEC" || tipo == "LOG")
    {
        qDebug() << "Tipo:" << tipo.c_str();
        inicio = log10(inicio);
        fim = log10(fim);
    }
    else
        intervalo = (fim - inicio) / pontos;
    for (wlog = inicio; wlog < fim + intervalo / 2; wlog += intervalo)
    {
        if (tipo == "OCT")
            w = pow(10, wlog);
        else if (tipo == "DEC" || tipo == "LOG")
            w = pow(10, wlog);
        else
            w = wlog;
        qDebug() << "Tipo:" << tipo.c_str();
        qDebug() << "w:" << w;
        *out << endl << w;
        qDebug() << "w:" << w;
        montaMatriz(w * 2 * M_PI, "");
        resolveSistema();
    }
    delete out;
    out = 0;
    arquivoTabela.close();
}

Circuito::Circuito(char* nomeArquivo)
{
    int i;
    double w;
    listaInc.push_back("0");
    listaNo.push_back("0");
    leNetlist(nomeArquivo);
    e = new Complexo[listaInc.size()];
    b = new Complexo[listaInc.size()];
    G = new Complexo*[listaInc.size()];
    fout.open("teste3.tab");
    fout<< "f";
    for (i = 0; i < listaInc.size(); i++)
    {
        G[i] = new Complexo[listaInc.size()];
        if (i!=0)
            fout << " " << listaInc[i] + "m" << " " << listaInc[i] + "f";
    }
    for (w = -3; w <= 2; w += 2.0/198)
    {
        fout << std::endl << pow(10,w);
        montaMatriz(pow(10, w) * 2 * M_PI, "");
        resolveSistema();
    }
    fout.close();
}

void Circuito::leNetlist(char* nomeArquivo)
{
    int i;
    char c;
    double cbe, cbc;
    Indutor *l1 = 0;
    Indutor *l2 = 0;
    std::ifstream fin(nomeArquivo);
    std::string nome;
    std::string no[4];
    double valor[4];
    if (fin.is_open())
    {
        getline(fin, nome); //pula primeira linha
        Elemento* elemento;
        bool sair = false;
        while(/*(getline(fin, linha)*/ fin >> nome)
        {
            elemento = 0;
            switch (nome[0])
            {
                case 'R':
                    fin >> no[0] >> no[1] >> valor[0];
                    elemento = new Resistor(nome, adicionaNo(no[0]), adicionaNo(no[1]), valor[0]);
                    break;
                case 'L':
                    fin >> no[0] >> no[1] >> valor[0];
                    elemento = new Indutor(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaInc("j" + nome), valor[0]);
                    break;
                case 'K':
                    fin >> no[0] >> no[1] >> valor[0];
                    for(i = 0; i < listaElementos.size(); i++)
                    {
                        if (no[0] == listaElementos[i]->getNome())
                            l1 = (Indutor*)(listaElementos[i]);
                        if (no[1] == listaElementos[i]->getNome())
                            l2 = (Indutor*)(listaElementos[i]);
                    }
                    elemento = new IndutanciaMutua(l1->getNome() + l2->getNome(), l1, l2, valor[0]);
                    break;
                case 'C':
                    fin >> no[0] >> no[1] >> valor[0];
                    elemento = new Capacitor(nome, adicionaNo(no[0]), adicionaNo(no[1]), valor[0]);
                    break;
                case 'E':
                    fin >> no[0] >> no[1] >> no[2] >> no[3] >> valor[0];
                    elemento = new AmpDeTensao(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaNo(no[2]), adicionaNo(no[3]), adicionaInc("j" + nome), valor[0]);
                    break;
                case 'F':
                    fin >> no[0] >> no[1] >> no[2] >> no[3] >> valor[0];
                    elemento = new AmpDeCorrente(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaNo(no[2]), adicionaNo(no[3]), adicionaInc("j" + nome), valor[0]);
                    break;
                case 'G':
                    fin >> no[0] >> no[1] >> no[2] >> no[3] >> valor[0];
                    elemento = new Transcondutor(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaNo(no[2]), adicionaNo(no[3]), valor[0]);
                    break;
                case 'H':
                    fin >> no[0] >> no[1] >> no[2] >> no[3] >> valor[0];
                    elemento = new Transresistor(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaNo(no[2]), adicionaNo(no[3]), adicionaInc("jx" + nome), adicionaInc("jy" + nome), valor[0]);
                    break;
                case 'I':
                    fin >> no[0] >> no[1] >> valor[0] >> valor[1];
                    elemento = new FonteCorrente(nome, adicionaNo(no[0]), adicionaNo(no[1]), valor[0], valor[1]);
                    break;
                case 'V':
                    fin >> no[0] >> no[1] >> valor[0] >> valor[1];
                    elemento = new FonteTensao(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaInc("j" + nome), valor[0], valor[1]);
                    break;
                case 'O':
                    fin >> no[0] >> no[1] >> no[2] >> no[3];
                    elemento = new AmpOp(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaNo(no[2]), adicionaNo(no[3]), adicionaInc("j" + nome));
                    break;
                case 'Q':
                    fin >> no[0] >> no[1] >> no[2] >> valor[0] >> valor[1] >> valor[2] >> valor[3];
                    c = fin.peek();
                    if (c == '\n')
                        elemento = new TransBipolar(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaNo(no[2]), adicionaInc("j" + nome), valor[0], valor[1], valor[2], valor[3]);
                    else
                    {
                        fin >> cbe >> cbc;
                        elemento = new TransBipolar(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaNo(no[2]), adicionaInc("j" + nome), valor[0], valor[1], valor[2], valor[3], cbe, cbc);
                    }
                    break;
                case '.':
                    sair = true;
                    break;
            }
            if (sair)
                break;
            if (elemento)
                listaElementos.push_back(elemento);
        }
    }
    fin.close();
}

void Circuito::leNetlistQT(QString nomeArquivo)
{
    QFile arquivo(nomeArquivo);
    if (!arquivo.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&arquivo);
    int i;
    double cbe, cbc;
    Indutor *l1 = 0;
    Indutor *l2 = 0;
    QString nome2;
    std::string nome;
    QString no2[4];
    std::string no[4];
    double valor[4];
    in.readLine(); //pula primeira linha
    Elemento* elemento;
    bool sair = false;
    while(!in.atEnd())
    {
        in >> nome2;
        qDebug() << "NOME:" << nome2;
        if(in.status() != QTextStream::Ok)
        {
            qDebug() << "Status:" << in.status();
            qDebug() << "Ok:" << QTextStream::Ok;
            qDebug() << "Saiu1";
            break;
        }
        nome = nome2.toStdString();
        elemento = 0;
        qDebug() << "NOME:" << nome.c_str();
        switch (nome[0])
        {
        case 'R':
            in >> no2[0] >> no2[1] >> valor[0];
            no[0] = no2[0].toStdString();
            no[1] = no2[1].toStdString();
            elemento = new Resistor(nome, adicionaNo(no[0]), adicionaNo(no[1]), valor[0]);
            break;
        case 'L':
            in >> no2[0] >> no2[1] >> valor[0];
            no[0] = no2[0].toStdString();
            no[1] = no2[1].toStdString();
            elemento = new Indutor(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaInc("j" + nome), valor[0]);
            break;
        case 'K':
            in >> no2[0] >> no2[1] >> valor[0];
            no[0] = no2[0].toStdString();
            no[1] = no2[1].toStdString();
            for(i = 0; i < listaElementos.size(); i++)
            {
                if (no[0] == listaElementos[i]->getNome())
                    l1 = (Indutor*)(listaElementos[i]);
                if (no[1] == listaElementos[i]->getNome())
                    l2 = (Indutor*)(listaElementos[i]);
            }
            elemento = new IndutanciaMutua(l1->getNome() + l2->getNome(), l1, l2, valor[0]);
            break;
        case 'C':
            in >> no2[0] >> no2[1] >> valor[0];
            no[0] = no2[0].toStdString();
            no[1] = no2[1].toStdString();
            elemento = new Capacitor(nome, adicionaNo(no[0]), adicionaNo(no[1]), valor[0]);
            break;
        case 'E':
            in >> no2[0] >> no2[1] >> no2[2] >> no2[3] >> valor[0];
            no[0] = no2[0].toStdString();
            no[1] = no2[1].toStdString();
            no[2] = no2[2].toStdString();
            no[3] = no2[3].toStdString();
            elemento = new AmpDeTensao(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaNo(no[2]), adicionaNo(no[3]), adicionaInc("j" + nome), valor[0]);
            break;
        case 'F':
            in >> no2[0] >> no2[1] >> no2[2] >> no2[3] >> valor[0];
            no[0] = no2[0].toStdString();
            no[1] = no2[1].toStdString();
            no[2] = no2[2].toStdString();
            no[3] = no2[3].toStdString();
            elemento = new AmpDeCorrente(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaNo(no[2]), adicionaNo(no[3]), adicionaInc("j" + nome), valor[0]);
            break;
        case 'G':
            in >> no2[0] >> no2[1] >> no2[2] >> no2[3] >> valor[0];
            no[0] = no2[0].toStdString();
            no[1] = no2[1].toStdString();
            no[2] = no2[2].toStdString();
            no[3] = no2[3].toStdString();
            elemento = new Transcondutor(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaNo(no[2]), adicionaNo(no[3]), valor[0]);
            break;
        case 'H':
            in >> no2[0] >> no2[1] >> no2[2] >> no2[3] >> valor[0];
            no[0] = no2[0].toStdString();
            no[1] = no2[1].toStdString();
            no[2] = no2[2].toStdString();
            no[3] = no2[3].toStdString();
            elemento = new Transresistor(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaNo(no[2]), adicionaNo(no[3]), adicionaInc("jx" + nome), adicionaInc("jy" + nome), valor[0]);
            break;
        case 'I':
            in >> no2[0] >> no2[1] >> valor[0];
            no[0] = no2[0].toStdString();
            no[1] = no2[1].toStdString();
            if (nome2[0] == '\n')
                elemento = new FonteCorrente(nome, adicionaNo(no[0]), adicionaNo(no[1]), valor[0], valor[1]);
            else
            {
                in >> valor[1];
                elemento = new FonteCorrente(nome, adicionaNo(no[0]), adicionaNo(no[1]), valor[0], valor[1]);
            }
            break;
        case 'V':
            in >> no2[0] >> no2[1] >> valor[0];
            no[0] = no2[0].toStdString();
            no[1] = no2[1].toStdString();
            in.seek(in.pos() + 1);
            nome2 = in.read(1);
            in.seek(in.pos() - 2);
            in.flush();
            if (nome2[0] == '\n')
            {
                qDebug() << "n OK!!!";
                elemento = new FonteTensao(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaInc("j" + nome), valor[0]);
            }
            else
            {
                qDebug() << "Errado!!!";
                in >> valor[1];
                elemento = new FonteTensao(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaInc("j" + nome), valor[0], valor[1]);
            }
            break;
        case 'O':
            in >> no2[0] >> no2[1] >> no2[2] >> no2[3];
            no[0] = no2[0].toStdString();
            no[1] = no2[1].toStdString();
            no[2] = no2[2].toStdString();
            no[3] = no2[3].toStdString();
            elemento = new AmpOp(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaNo(no[2]), adicionaNo(no[3]), adicionaInc("j" + nome));
            break;
        case 'Q':
            in >> no2[0] >> no2[1] >> no2[2] >> valor[0] >> valor[1] >> valor[2] >> valor[3];
            no[0] = no2[0].toStdString();
            no[1] = no2[1].toStdString();
            no[2] = no2[2].toStdString();
            in.seek(in.pos() + 1);
            nome2 = in.read(1);
            in.seek(in.pos() - 2);
            in.flush();
            if (nome2[0] == '\n')
            {
                elemento = new TransBipolar(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaNo(no[2]), adicionaInc("j" + nome), valor[0], valor[1], valor[2], valor[3]);
            }
            else
            {
                in >> cbe >> cbc;
                elemento = new TransBipolar(nome, adicionaNo(no[0]), adicionaNo(no[1]), adicionaNo(no[2]), adicionaInc("j" + nome), valor[0], valor[1], valor[2], valor[3], cbe, cbc);
            }
            break;
        case '.':
            in >> nome2 >> pontos >> inicio >> fim;
            tipo = nome2.toStdString();
            sair = true;
            break;
        }
        if (sair)
        {
            qDebug() << "Saiu2";
            break;
        }
        if (elemento)
            listaElementos.push_back(elemento);
    }
    arquivo.close();
}

int Circuito::adicionaNo(std::string nome)
{
    int i;
    for (i = 0; i < listaNo.size(); i++)
        if (listaNo[i] == nome)
            for (i = 0; i < listaInc.size(); i++)
                if (listaInc[i] == nome)
                    return i;
    //nNos++;
    listaNo.push_back(nome);
    return adicionaInc(nome);
}

int Circuito::adicionaInc(std::string nome)
{
    listaInc.push_back(nome);
    return listaInc.size() - 1;
}

//Tipo serve pra identificar freq
void Circuito::montaMatriz(double w, std::string tipo)
{
    int i, j;
    for (i = 0; i < listaInc.size(); i++)
    {
        e[i] = 0;
        b[i] = 0;
        for (j = 0; j < listaInc.size(); j++)
            G[i][j] = 0;
    }
    qDebug() << listaElementos.size();
    for (i = 0; i < listaElementos.size(); i++)
        listaElementos[i]->somaEstampa(w, G, b);
}

void Circuito::resolveSistema()
{
    Complexo sub;
    int p[listaInc.size() - 1];
    int i, j, k, aux;
    for (i = 0; i < listaInc.size() - 1; i++)
        p[i] = i + 1;
    for (i = 0; i < listaInc.size() - 2; i++)
    {
        for (j = i + 1; j < listaInc.size() - 1; j++)
            if (G[p[j]][i + 1].calculaModulo() > G[p[i]][i + 1].calculaModulo())
            {
                aux = p[i];
                p[i] = p[j];
                p[j] = aux;
            }
        for (j = i + 1; j < listaInc.size() - 1; j++)
        {
            sub = G[p[j]][i + 1] / G[p[i]][i + 1];
            for (k = i; k < listaInc.size() - 1; k++)
                G[p[j]][k + 1] -= (G[p[i]][k + 1] * sub);
            b[p[j]] -= (b[p[i]] * sub);
        }
    }

    for (i = listaInc.size() - 2; i >= 0; i--)
    {
        sub = b[p[i]];
        for (j = i + 1; j < listaInc.size() - 1; j++)
            sub -= G[p[i]][j + 1] * e[j + 1];
        e[i + 1] = sub / G[p[i]][i + 1];
    }

    /*for (k = 0; k < listaInc.size(); k++)
        {
            std::cout << std::setprecision(1);
            for (j = 0; j < listaInc.size(); j++)
                std::cout << "|   "<< j << G[k][j].getA() << "+" << G[k][j].getB() << "i   ";
            std::cout << std::endl << std::endl;
        }
            std::cout << std::endl << std::endl;*/
    for (i = 1; i < listaInc.size(); i++)
    {
        *out << " " << e[i].calculaModulo() << " " << e[i].calculaFase() * 180 / M_PI;
        //fout << " " << e[i].calculaModulo() << " " << e[i].calculaFase() * 180 / M_PI;
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "circuito.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graficoWidget->setInteraction(QCP::iRangeDrag, true);
    ui->graficoWidget->setInteraction(QCP::iRangeZoom , true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbrir_triggered()
{
    QString nomeArquivo = QFileDialog::getOpenFileName(this, tr("Abrir Netlist"), QString(),
            tr("Netlists (*.net);;Todos os Arquivos (*.*)"));

    if (!nomeArquivo.isEmpty())
        Circuito c(nomeArquivo);
}

void MainWindow::on_actionAbrirGrafico_triggered()
{
    double maxX, minX, maxY, minY;
    QVector< QVector<double> > y;
    QString linha;
    QStringList variaveis, aux;
    QString nomeArquivo = QFileDialog::getOpenFileName(this, tr("Abrir Tabela"), QString(),
            tr("Tabelas (*.tab);;Todos os Arquivos (*.*)"));
    if (!nomeArquivo.isEmpty())
    {
        QFile file(nomeArquivo);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Erro"), tr("Não foi possível abrir o arquivo"));
            return;
        }
        QTextStream in(&file);
        linha = in.readLine();
        variaveis = linha.split(' ');
        for(int i = 0; i < variaveis.size(); i++)
        {
            QVector<double> z;
            y.push_back(z);
        }
        while (!in.atEnd())
        {
            linha = in.readLine();
            if (in.status() != QTextStream::Ok)
                break;
            aux = linha.split(' ');
            for (int i = 0; i < aux.size(); i++)
                y[i].push_back(aux[i].toDouble());
        }
        file.close();
        if (variaveis.size() > 1)
        {
            int n = 1;
            for (int i = 0; i < variaveis.size(); i++)
                if (variaveis[i] == ui->linhaNGraf->text())
                    n = i;
            ui->graficoWidget->addGraph();
            ui->graficoWidget->graph(0)->setData(y[0], y[n]);
            minX = maxX = y[0][0];
            minY = maxY = y[n][0];
            for (int i = 1; i < y[0].size(); i++)
            {
                if (y[0][i] > maxX)
                    maxX = y[0][i];
                if (y[0][i] < minX)
                    minX = y[0][i];
                if (y[n][i] > maxY)
                    maxY = y[n][i];
                if (y[n][i] < minY)
                    minY = y[n][i];
            }
            ui->graficoWidget->xAxis->setLabel(variaveis[0]);
            ui->graficoWidget->yAxis->setLabel(variaveis[n]);
            ui->graficoWidget->xAxis->setRange(minX, maxX);
            ui->graficoWidget->yAxis->setRange(minY, maxY);
            ui->graficoWidget->replot();
        }
    }
}

void MainWindow::on_actionSobre_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Programa MNA versão 0.8");
    msgBox.setInformativeText("Autores: Artur Andrade Motta Sarlo \n\t João Vítor Ferreira Duarte \n\t Pedro de Carvalho Cayres Pinto");
    msgBox.exec();
}

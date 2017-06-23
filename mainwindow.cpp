#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    matrizA(0),
    matrizB(0)
{
    ui->setupUi(this);
    ui->pushButtonApagarA->setEnabled(false);
    ui->pushButtonApagarB->setEnabled(false);
    ui->pushButtonSoma->setEnabled(false);
    ui->pushButtonSubtracao->setEnabled(false);
    ui->pushButtonMultiplicacao->setEnabled(false);
    ui->textEditMatrizA->setEnabled(false);
    ui->textEditMatrizB->setEnabled(false);
    ui->textEditResultado->setEnabled(false);
    ui->pushButtonTranspostaA->setEnabled(false);
    ui->pushButtonTranspostaB->setEnabled(false);
    ui->pushButtonMultiplicarKA->setEnabled(false);
    ui->pushButtonMultiplicarKB->setEnabled(false);
    ui->lineEditKB->setEnabled(false);
    ui->lineEditKA->setEnabled(false);
    ui->lineEditPotenciaA->setEnabled(false);
    ui->pushButtonPotenciaA->setEnabled(false);
    ui->lineEditPotenciaB->setEnabled(false);
    ui->pushButtonPotenciaB->setEnabled(false);
    ui->tableWidget->setEnabled(false);
}

MainWindow::~MainWindow()
{
    if(matrizA) delete matrizA;
    if(matrizB) delete matrizB;
    delete ui;
}

void MainWindow::on_pushButtonCriarA_clicked()
{
    try{
        int linha = ui->lineEditQuantidadeDeLinhasA->text().toInt();
        int coluna = ui->lineEditQuantidadeDeColunasA->text().toInt();

        matrizA = new TP2::Matriz(linha,coluna);

        for(int l=0; l < linha; l++){
            for(int c = 0; c < coluna; c++){
                int elemento = QInputDialog::getInt(this, "Leitura", "Matriz A ["+QString::number(l)+", "+ QString::number(c)+"] = ");
                matrizA->setElemento(l,c,elemento);
            }
        }

        ui->textEditMatrizA->setText(matrizA->getConjunto());

        ui->pushButtonApagarA->setEnabled(true);
        ui->pushButtonCriarA->setEnabled(false);
        ui->lineEditQuantidadeDeColunasA->setEnabled(false);
        ui->lineEditQuantidadeDeLinhasA->setEnabled(false);
        ui->pushButtonCriarA->setEnabled(false);
        ui->pushButtonTranspostaA->setEnabled(true);
        ui->pushButtonMultiplicarKA->setEnabled(true);
        ui->lineEditKA->setEnabled(true);
        ui->lineEditPotenciaA->setEnabled(true);
        ui->pushButtonPotenciaA->setEnabled(true);

        QString resultadoA;

        if(matrizA->eTriangularSuperior())
            resultadoA = "Sim";
        else
            resultadoA = "Nao";

        QTableWidgetItem *item1 = new QTableWidgetItem(resultadoA);
        ui->tableWidget->setItem(2,0,item1);

        if(matrizA->eTriangularInferior())
            resultadoA = "Sim";
        else
            resultadoA = "Nao";

        item1 = new QTableWidgetItem(resultadoA);
        ui->tableWidget->setItem(3,0,item1);

        if(matrizA->eIdentidade())
            resultadoA = "Sim";
        else
            resultadoA = "Nao";

        item1 = new QTableWidgetItem(resultadoA);
        ui->tableWidget->setItem(4,0,item1);

        if(matrizA->eSimetrica())
            resultadoA = "Sim";
        else
            resultadoA = "Nao";

        item1 = new QTableWidgetItem(resultadoA);
        ui->tableWidget->setItem(5,0,item1);


        if(matrizA->eMatrizOrtogonal())
            resultadoA = "Sim";
        else
            resultadoA = "Nao";

        item1 = new QTableWidgetItem(resultadoA);
        ui->tableWidget->setItem(6,0,item1);

        if(matrizA->eMatrizDePermutacao())
            resultadoA = "Sim";
        else
            resultadoA = "Nao";

        item1 = new QTableWidgetItem(resultadoA);
        ui->tableWidget->setItem(7,0,item1);

        if(matrizB){
            ui->pushButtonSoma->setEnabled(true);
            ui->pushButtonSubtracao->setEnabled(true);
            ui->pushButtonMultiplicacao->setEnabled(true);

            QString resultadoA;

            if((*matrizA) == matrizB)
                resultadoA = "Sim";
            else
                resultadoA = "Nao";

            QTableWidgetItem *item1 = new QTableWidgetItem(resultadoA);
            ui->tableWidget->setItem(0,0,item1);

            if((*matrizA) != matrizB)
                resultadoA = "Sim";
            else
                resultadoA = "Nao";

            item1 = new QTableWidgetItem(resultadoA);
            ui->tableWidget->setItem(1,0,item1);

        }
    }catch(QString &erro){
        QMessageBox::information(this, "ERRO", erro);
    }catch(std::bad_alloc&){
        QMessageBox::information(this, "ERRO",  "Matriz nao pode ser criada");
    }
}

void MainWindow::on_pushButtonApagarA_clicked()
{
    try{
        delete matrizA;

        matrizA = 0;

        ui->pushButtonApagarA->setEnabled(false);
        ui->pushButtonSoma->setEnabled(false);
        ui->pushButtonSubtracao->setEnabled(false);
        ui->pushButtonMultiplicacao->setEnabled(false);
        ui->pushButtonCriarA->setEnabled(true);
        ui->lineEditQuantidadeDeColunasA->clear();
        ui->lineEditQuantidadeDeColunasA->setEnabled(true);
        ui->lineEditQuantidadeDeLinhasA->clear();
        ui->lineEditQuantidadeDeLinhasA->setEnabled(true);
        ui->textEditMatrizA->clear();
        ui->textEditResultado->clear();
        ui->pushButtonTranspostaA->setEnabled(false);
        ui->pushButtonMultiplicarKA->setEnabled(false);
        ui->lineEditKA->setEnabled(false);
        ui->lineEditKA->clear();
        ui->lineEditPotenciaA->clear();
        ui->lineEditPotenciaA->setEnabled(false);
        ui->pushButtonPotenciaA->setEnabled(false);
    }catch(...){
        QMessageBox::information(this, "ERRO", "ERRO NO METODO DE APAGAR O OBJETO");
    }
}

void MainWindow::on_pushButtonCriarB_clicked()
{
    try{
        int linha = ui->lineEditQuantidadeDeLinhasB->text().toInt();
        int coluna = ui->lineEditQuantidadeDeColunasB->text().toInt();

        matrizB = new TP2::Matriz(linha,coluna);

        for(int l = 0; l < linha; l++){
            for(int c = 0; c < coluna; c++){
                int elemento = QInputDialog::getInt(this, "Leitura", "Matriz B ["+QString::number(l)+", "+ QString::number(c)+"] = ");
                matrizB->setElemento(l,c,elemento);
            }
        }

        ui->textEditMatrizB->setText(matrizB->getConjunto());

        ui->pushButtonApagarB->setEnabled(true);
        ui->pushButtonCriarB->setEnabled(false);
        ui->lineEditQuantidadeDeColunasB->setEnabled(false);
        ui->lineEditQuantidadeDeLinhasB->setEnabled(false);
        ui->pushButtonCriarB->setEnabled(false);
        ui->pushButtonTranspostaB->setEnabled(true);
        ui->pushButtonMultiplicarKB->setEnabled(true);
        ui->lineEditKB->setEnabled(true);
        ui->lineEditPotenciaB->setEnabled(true);
        ui->pushButtonPotenciaB->setEnabled(true);

        QString resultadoB;

        if(matrizB->eTriangularSuperior())
            resultadoB = "Sim";
        else
            resultadoB = "Nao";

        QTableWidgetItem *item1 = new QTableWidgetItem(resultadoB);
        ui->tableWidget->setItem(2,1,item1);

        if(matrizB->eTriangularInferior())
            resultadoB = "Sim";
        else
            resultadoB = "Nao";

        item1 = new QTableWidgetItem(resultadoB);
        ui->tableWidget->setItem(3,1,item1);

        if(matrizB->eIdentidade())
            resultadoB = "Sim";
        else
            resultadoB = "Nao";

        item1 = new QTableWidgetItem(resultadoB);
        ui->tableWidget->setItem(4,1,item1);

        if(matrizB->eSimetrica())
            resultadoB = "Sim";
        else
            resultadoB = "Nao";

        item1 = new QTableWidgetItem(resultadoB);
        ui->tableWidget->setItem(5,1,item1);

        if(matrizB->eMatrizOrtogonal())
            resultadoB = "Sim";
        else
            resultadoB = "Nao";

        item1 = new QTableWidgetItem(resultadoB);
        ui->tableWidget->setItem(6,1,item1);

        if(matrizB->eMatrizDePermutacao())
            resultadoB = "Sim";
        else
            resultadoB = "Nao";

        item1 = new QTableWidgetItem(resultadoB);
        ui->tableWidget->setItem(7,1,item1);

        if(matrizA){
            ui->pushButtonSoma->setEnabled(true);
            ui->pushButtonSubtracao->setEnabled(true);
            ui->pushButtonMultiplicacao->setEnabled(true);

            QString resultadoA;

            if((*matrizA) == matrizB)
                resultadoA = "Sim";
            else
                resultadoA = "Nao";

            QTableWidgetItem *item1 = new QTableWidgetItem(resultadoA);
            ui->tableWidget->setItem(0,0,item1);

            if((*matrizA) != matrizB)
                resultadoA = "Sim";
            else
                resultadoA = "Nao";

            item1 = new QTableWidgetItem(resultadoA);
            ui->tableWidget->setItem(1,0,item1);
        }
    }catch(QString &erro){
        QMessageBox::information(this, "ERRO", erro);
    }catch(std::bad_alloc&){
        QMessageBox::information(this, "ERRO",  "Matriz nao pode ser criada");
    }
}

void MainWindow::on_pushButtonApagarB_clicked()
{
    try{
        delete matrizB;

        matrizB = 0;

        ui->pushButtonApagarB->setEnabled(false);
        ui->pushButtonSoma->setEnabled(false);
        ui->pushButtonSubtracao->setEnabled(false);
        ui->pushButtonMultiplicacao->setEnabled(false);
        ui->pushButtonCriarB->setEnabled(true);
        ui->lineEditQuantidadeDeColunasB->clear();
        ui->lineEditQuantidadeDeColunasB->setEnabled(true);
        ui->lineEditQuantidadeDeLinhasB->clear();
        ui->lineEditQuantidadeDeLinhasB->setEnabled(true);
        ui->textEditMatrizB->clear();
        ui->textEditResultado->clear();
        ui->pushButtonTranspostaB->setEnabled(false);
        ui->pushButtonMultiplicarKB->setEnabled(false);
        ui->lineEditKB->setEnabled(false);
        ui->lineEditKB->clear();
        ui->lineEditPotenciaB->clear();
        ui->lineEditPotenciaB->setEnabled(false);
        ui->pushButtonPotenciaB->setEnabled(false);
    }catch(...){
        QMessageBox::information(this, "ERRO", "ERRO NO METODO DE APAGAR O OBJETO");
    }
}

void MainWindow::on_pushButtonSoma_clicked()
{
    try{
        TP2::Matriz* resultado = 0;

        resultado = (*matrizA) + matrizB;
        ui->textEditResultado->setText(resultado->getConjunto());

        delete resultado;
    }catch(QString &erro){
        QMessageBox::information(this, "ERRO", erro);
    }
}

void MainWindow::on_pushButtonSubtracao_clicked()
{
    try{
        TP2::Matriz* resultado = 0;

        resultado = (*matrizA) - matrizB;
        ui->textEditResultado->setText(resultado->getConjunto());

        delete resultado;
    }catch(QString &erro){
        QMessageBox::information(this, "ERRO", erro);
    }
}

void MainWindow::on_pushButtonMultiplicacao_clicked()
{
    try{
        TP2::Matriz* resultado = 0;

        resultado = (*matrizA) * matrizB;
        ui->textEditResultado->setText(resultado->getConjunto());

        delete resultado;
    }catch(QString &erro){
        QMessageBox::information(this, "ERRO", erro);
    }
}

void MainWindow::on_pushButtonTranspostaA_clicked()
{
    try{
        TP2::Matriz* resultado = 0;

        resultado = matrizA->transposta();

        ui->textEditResultado->setText(resultado->getConjunto());

        delete resultado;
    }catch(QString &erro){
        QMessageBox::information(this, "ERRO", erro);
    }
}

void MainWindow::on_pushButtonTranspostaB_clicked()
{
    try{
        TP2::Matriz* resultado = 0;

        resultado = matrizB->transposta();

        ui->textEditResultado->setText(resultado->getConjunto());

        delete resultado;
    }catch(QString &erro){
        QMessageBox::information(this, "ERRO", erro);
    }
}

void MainWindow::on_pushButtonMultiplicarKA_clicked()
{
    try{
        TP2::Matriz* resultado = 0;

        int k = ui->lineEditKA->text().toInt();

        resultado = matrizA->multiplicacaoK(k);

        ui->textEditResultado->setText(resultado->getConjunto());

        delete resultado;
    }catch(QString &erro){
        QMessageBox::information(this, "ERRO", erro);
    }
}

void MainWindow::on_pushButtonMultiplicarKB_clicked()
{
    try{
        TP2::Matriz* resultado = 0;

        int k = ui->lineEditKB->text().toInt();

        resultado = matrizB->multiplicacaoK(k);

        ui->textEditResultado->setText(resultado->getConjunto());

        delete resultado;
    }catch(QString &erro){
        QMessageBox::information(this, "ERRO", erro);
    }
}

void MainWindow::on_pushButtonPotenciaA_clicked()
{
    try{
        TP2::Matriz* resultado = 0;

        int p = ui->lineEditPotenciaA->text().toInt();

        resultado = matrizA->potenciacao(p);

        ui->textEditResultado->setText(resultado->getConjunto());

        delete resultado;
    }catch(QString &erro){
        QMessageBox::information(this, "ERRO", erro);
    }
}

void MainWindow::on_pushButtonPotenciaB_clicked()
{
    try{
        TP2::Matriz* resultado = 0;

        int p = ui->lineEditPotenciaB->text().toInt();

        resultado = matrizB->potenciacao(p);

        ui->textEditResultado->setText(resultado->getConjunto());

        delete resultado;
    }catch(QString &erro){
        QMessageBox::information(this, "ERRO", erro);
    }
}

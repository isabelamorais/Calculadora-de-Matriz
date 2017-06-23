#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <Matriz.h>
#include <QMessageBox>
#include <QInputDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonCriarA_clicked();

    void on_pushButtonApagarA_clicked();

    void on_pushButtonCriarB_clicked();

    void on_pushButtonApagarB_clicked();

    void on_pushButtonSoma_clicked();

    void on_pushButtonSubtracao_clicked();

    void on_pushButtonMultiplicacao_clicked();

    void on_pushButtonTranspostaA_clicked();

    void on_pushButtonTranspostaB_clicked();

    void on_pushButtonMultiplicarKA_clicked();

    void on_pushButtonMultiplicarKB_clicked();

    void on_pushButtonPotenciaA_clicked();

    void on_pushButtonPotenciaB_clicked();

private:
    Ui::MainWindow *ui;
    TP2::Matriz *matrizA;
    TP2::Matriz *matrizB;
};

#endif // MAINWINDOW_H

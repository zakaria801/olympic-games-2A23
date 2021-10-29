#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pays.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
   int classement=ui->le_classement->text().toInt();
   QString Nom=ui->le_Nom->text();
   QString continent=ui->le_continent->text();
   QString IP_adresse=ui->le_IP->text();




}

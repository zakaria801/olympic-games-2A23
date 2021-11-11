#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pays.h"
#include <QMessageBox>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_classement->setValidator(new QIntValidator(100,999999,this));
    ui->le_NB_athletes->setValidator(new QIntValidator(100,99999,this));
    ui->tab_pays->setModel(p.afficher());


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pb_ajouter_clicked()
{
   int classement=ui->le_classement->text().toInt();
   QString Nom=ui->le_Nom->text();
   int NB_athletes=ui->le_NB_athletes->text().toInt();
   QString IP_adresse=ui->le_IP->text();
   pays p(NB_athletes,IP_adresse,Nom,classement);
   bool test=p.ajouter();
   if(test)
   {
       ui->tab_pays->setModel(p.afficher());
       QMessageBox::information(nullptr,QObject::tr("ok"),QObject::tr("click cancel to exit"),QMessageBox::Cancel);
   }else
   {
       QMessageBox::critical(nullptr,QObject::tr("not ok"),QObject::tr("click cancel to exit"),QMessageBox::Cancel);
   }
}





void MainWindow::on_pb_supprimer_clicked()
{
  pays p1; p1.setIP_adresse(ui->le_IP_adresse_supp->text());
  bool test=p1.supprimer(p1.getIP_adresse());
if (test)
{
    QMessageBox::information(nullptr,QObject::tr("ok"),
    QObject::tr("suppression effectuée\n"
    "click cancel to exit"),QMessageBox::Cancel);
}
else
{
    QMessageBox::critical(nullptr,QObject::tr(" Not ok"),
    QObject::tr("suppression non effectuée\n"
    "click cancel to exit"),QMessageBox::Cancel);
}
}


void MainWindow::on_pb_modifier_clicked()
{
    int NB_athletes=ui->le_NB_athletes_2->text().toInt();
       QString Nom=ui->le_Nom_2->text();
           QString IP_adresse =ui->le_IP_2->text();
           int classement=ui->le_classement_2->text().toInt();
            p.setNom(Nom);
            p.setclassement(classement);
            p.setNB_athletes(NB_athletes);


           bool test=p.modifier(IP_adresse);
           if (test)
           {
               QMessageBox::information(nullptr,QObject::tr("ok"),
               QObject::tr("modifier effectuée\n"
               "click cancel to exit"),QMessageBox::Cancel);
           }
           else
           {
               QMessageBox::critical(nullptr,QObject::tr(" Not ok"),
               QObject::tr("modifier non effectuée\n"
               "click cancel to exit"),QMessageBox::Cancel);
           }
}




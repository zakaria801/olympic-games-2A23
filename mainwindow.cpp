#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pays.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QtDebug>
#include "historique.h"
#include "history.h"
#include<QString>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include <QDesktopServices>
#include <QSqlQuery>



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
    QString IP_adresse =ui->le_IP_2->text();
    QString Nom=ui->le_Nom_2->text();
    int NB_athletes=ui->le_NB_athletes_2->text().toInt();


           int classement=ui->le_classement_2->text().toInt();
           pays p1(classement,IP_adresse,Nom,NB_athletes);


         //   qDebug()<<"jhjkhkjh";


           bool test=p1.modifier();
           //qDebug()<<"jhjkhkjh";

           if (test)
           {

               QMessageBox::information(nullptr,QObject::tr("ok"),
               QObject::tr("modifier effectuée\n"
               "click cancel to exit"),QMessageBox::Cancel);
               ui->tab_pays->setModel(p1.afficher());
           }
           else
           {
               QMessageBox::critical(nullptr,QObject::tr(" Not ok"),
               QObject::tr("modifier non effectuée\n"
               "click cancel to exit"),QMessageBox::Cancel);
           }
}






void MainWindow::on_rech_clicked()
{
    QString val=ui->le_rech->text();
       QString option=ui->cb_rech->currentText();
       if((val!="")&&(option=="CLASSEMENT"))
   {        ui->tab_pays->setModel(p.afficher_recherche1(val));}
       else if((val!="")&&(option=="NB_ATHLETE"))
       {
          ui->tab_pays->setModel(p.afficher_recherche2(val));
       }
       else if((val!="")&&(option=="NOM"))
       {
          ui->tab_pays->setModel(p.afficher_recherche3(val));
       }else if((val!="")&&(option=="IP_ADRESSE"))
       {
          ui->tab_pays->setModel(p.afficher_recherche4(val));
       }else
       {
          ui->tab_pays->setModel(p.afficher());
       }
}



void MainWindow::on_cb_trie_activated(const QString &arg1)
{
    QString choix=ui->cb_trie->currentText();
        ui->tab_pays->setModel(p.afficher_choix(choix));
}

void MainWindow::on_pushButton_5_clicked()
{
close();
H = new Historique(this);
H->show();
}







void MainWindow::on_pushButton_clicked()
{
  QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                   "/home",
                                                   QFileDialog::ShowDirsOnly
                                                   | QFileDialog::DontResolveSymlinks);
       qDebug()<<dir;
       QPdfWriter pdf(dir+"/Pdfpays.pdf");                                 QPainter painter(&pdf);
                                int i = 4000;
                                     painter.setPen(Qt::red);

                                     painter.setFont(QFont("Arial", 30));
                                     painter.drawText(2100,1200,"Liste Des pays");
                                     painter.setPen(Qt::black);
                                     painter.setFont(QFont("Arial", 50));
                                     painter.drawRect(1000,200,6500,2000);
                                     painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap(":/homme.jpg"));
                                     painter.drawRect(0,3000,9600,500);
                                     painter.setFont(QFont("Arial", 9));
                                     painter.setPen(Qt::blue);
                                     painter.drawText(2300,3300,"IP-adresse");
                                     painter.drawText(4300,3300,"Nom");
                                     painter.drawText(6300,3300,"classement");
                                     painter.drawText(8300,3300,"NB_athlete");


                                     QSqlQuery query;
                                     query.prepare("select * from pays");
                                     query.exec();
                                     while (query.next())
                                     {
                                         painter.drawText(300,i,query.value(0).toString());
                                         painter.drawText(2300,i,query.value(1).toString());
                                         painter.drawText(4300,i,query.value(2).toString());
                                         painter.drawText(6300,i,query.value(3).toString());



                                        i = i +500;
                                     }
                                     int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?",
                                                                         QMessageBox::Yes |  QMessageBox::No);
                                         if (reponse == QMessageBox::Yes)
                                         {
                                             QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/PdfVoiture.pdf"));

                                             painter.end();
                                         }
                                         else
                                         {
                                              painter.end();
                                         }
}

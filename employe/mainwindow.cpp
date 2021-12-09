#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employe.h"
#include<QMessageBox>
#include <QIntValidator>
#include <QApplication>
#include <QObject>
#include "smtp.h"
#include <QFileDialog>
#include<QDate>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    makePolt();
    int ret=a.connect_arduino();
        switch (ret) {
        case(0):qDebug()<<"arduino is available and connected to :"<<a.getarduino_port_name();
            break;
        case(1):qDebug()<<"arduino is available but not connected to :"<<a.getarduino_port_name();
            break;
        case(-1):qDebug()<<"arduino is not available";
        }
  QObject::connect(a.getserial(),SIGNAL(readyRead()),this,SLOT(update_label()));
    QSqlQuery q("select * from employe");
    while(q.next()){
        //ui->comboBox->addItem(q.value(0).toString());

    }

    ui->lineEdit->setValidator ( new QIntValidator(0,999999, this));//ajoutid
   // ui->tableView_2->setModel(E.afficherC());
   // ui->lineEdit_5->setValidator( new QIntValidator(0,999999, this));//suppid//
    ui->lineEdit_2->setValidator ( new QIntValidator(0,999999, this));//modid

    ui->lineEdit_9->setValidator( new QIntValidator(0, 9999, this));//modsal
    ui->lineEdit_8->setValidator( new QIntValidator(0, 9999, this));//ajoutsal

    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
      connect(ui->browseBtn, SIGNAL(clicked()), this, SLOT(browse()));

    ui->tableView->setModel(E.afficher());
}
void MainWindow::update_label()
{
data=a.read_from_arduino();
if (data == "1")
{
    player->setMedia(QUrl::fromLocalFile("/path"));
    player->setVolume(50);
    player->play();
}
}
void MainWindow::makePolt()
{
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->customPlot->setBackground(QBrush(gradient));
    QCPBars *regen = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    regen->setAntialiased(false);
    regen->setStackingGap(1);
    regen->setName("Stat pandoud");
    regen->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    regen->setBrush(QColor(0, 168, 140));


    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 ;

    labels << "salaire >1000 " << "salaire <1000 " ;
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->customPlot->xAxis->setTicker(textTicker);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    ui->customPlot->xAxis->setSubTicks(false);
    ui->customPlot->xAxis->setTickLength(0, 4);
    ui->customPlot->xAxis->setRange(0, 8);
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0,20);
    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->setLabelColor(Qt::white);
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> regenData;
int nbr=0;

int he=0;
QSqlQuery query1("select count(*) from employe where salaire > 1000 ");
while (query1.next()) {

                        he = query1.value(0).toInt();

                                                    }

    QSqlQuery query2("select count(*) from employe where salaire < 1000 ");
    while (query2.next()) {
                           nbr = query2.value(0).toInt();

                             }
    regenData << he << nbr ;
    regen->setData(ticks, regenData);

    // setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);


}
void MainWindow::sendMail()
{
     Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toInt());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());


}

void MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}

void MainWindow::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}

MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_pushButton_2_clicked() //aajouut
{
int id= ui->lineEdit->text().toInt();
QString nom= ui->lineEdit_6->text();
QString prenom=ui->lineEdit_7->text();
QString date=ui->dateEdit->text();
int salaire=ui->lineEdit_8->text().toInt();
QString role=ui->lineEdit_10->text();
employe E(id,nom,prenom,date,salaire,role);

bool test=E.ajouter();
    if (test )
    {QMessageBox::information(nullptr,QObject::tr("succes"),
                QObject::tr("ajout effectué. \n"
                            "click to exit"),QMessageBox::Cancel);
         ui->tableView->setModel(E.afficher());
 }
else
        QMessageBox ::critical(nullptr,QObject::tr("failed"),
                               QObject::tr ("ajout non effectué.\n"
                                            "click to exit"),QMessageBox::Cancel);



}

void MainWindow::on_supp_clicked()
{
 employe E1;
   //int row=ui->tableView->selectionModel()->currentIndex().row();
  // int id=ui->tableView->model()->index(row,0).data().toInt();
    //bool test=E1.supprimer(E1.get_id());
    //int id=ui->line_chercher->text().toInt();
    //E1.set_id(ui->lineEdit_5->text().toInt());



   E1.set_id(ui->line_chercher->text().toInt());
   int id=ui->line_chercher->text().toInt();
   bool test;
   test= E1.supprimer(id);

   if (test )
   {QMessageBox::information(nullptr,QObject::tr("OK"),
               QObject::tr("suppresion effectuée. \n"
                           "click to exit"),QMessageBox::Cancel);
       ui->tableView->setModel(E.afficher());

   }
   else
       QMessageBox ::critical(nullptr,QObject::tr("not ok"),
                              QObject::tr ("suppresion non effectuée. \n"
                                           "click to exit"),QMessageBox::Cancel);
   }


void MainWindow::on_modifer_clicked()
{
     int  id= ui->lineEdit_2->text().toInt();
    QString nom= ui->lineEdit_3->text();
    QString prenom= ui->lineEdit_4->text();

    QString date= ui->date_2->text();
    int salaire = ui->lineEdit_9->text().toInt();
QString role=ui->lineEdit_10->text();
    employe E(id,nom,prenom,date,salaire,role);

        bool test=E.modifier(id);
        if(test)
       {

       QMessageBox::information(nullptr, QObject::tr("modifier un employé"),
                         QObject::tr("employee modifié.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tableView->setModel(E.afficher());

       }
         else
             QMessageBox::critical(nullptr, QObject::tr("modifier un employé"),
                         QObject::tr("Erreur !.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);

       }


void MainWindow::on_chercher_clicked()
{

  QString recherche =ui->line_chercher->text();
     ui->tableView->setModel(E.afficher_rech(recherche));


}

void MainWindow::on_pushButton_5_clicked()
{
    ui->tableView->setModel(E.afficher());
}



void MainWindow::on_tri_clicked()
{
     ui->tableView->setModel(E.tri());
}




void MainWindow::on_pushButton_6_clicked()   //exel***********
{
    QTableView *table;
          table = ui->tableView;

          QString filters("CSV files (*.csv);;All files (*.*)");
          QString defaultFilter("CSV files (*.csv)");
          QString fileName = QFileDialog::getSaveFileName(0, "Save file", QCoreApplication::applicationDirPath(),
                             filters, &defaultFilter);
          QFile file(fileName);

          QAbstractItemModel *model =  table->model();
          if (file.open(QFile::WriteOnly | QFile::Truncate)) {
              QTextStream data(&file);
              QStringList strList;
              for (int i = 0; i < model->columnCount(); i++) {
                  if (model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString().length() > 0)
                      strList.append("\"" + model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() + "\"");
                  else
                      strList.append("");
              }
              data << strList.join(";") << "\n";
              for (int i = 0; i < model->rowCount(); i++) {
                  strList.clear();
                  for (int j = 0; j < model->columnCount(); j++) {

                      if (model->data(model->index(i, j)).toString().length() > 0)
                          strList.append("\"" + model->data(model->index(i, j)).toString() + "\"");
                      else
                          strList.append("");
                  }
                  data << strList.join(";") + "\n";
              }
              file.close();
              QMessageBox::information(this,"Exporter To Excel","Exporter En Excel Avec Succées ");
          }
}








void MainWindow::on_line_chercher_textChanged(const QString &arg1)
{
    QString ch = arg1;

                     if (ch=="")
                     {
                         ui->tableView->setModel(E.afficher());
                     }
                     else {
                       ui->tableView->setModel(E.rechercherid(ch)) ;
    }
}








void MainWindow::on_pushButton_clicked()
{
    ui->tableView->setModel(E.tri1());
}

void MainWindow::on_pushButton_3_clicked()
{
   ui->tableView->setModel(E.tri2());
}



void MainWindow::on_commandLinkButton_clicked()
{
   ui->tabWidget_2->setCurrentIndex(4);
}

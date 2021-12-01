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
#include<QSqlQuery>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <string>
#include <QDebug>
#include <QMessageBox>







MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_classement->setValidator(new QIntValidator(100,999999,this));
    ui->le_NB_athletes->setValidator(new QIntValidator(100,99999,this));
    ui->tab_pays->setModel(p.afficher());

    ui->setupUi(this);
    ui->temp_lcdNumber->display("-------");
    arduino = new QSerialPort(this);
    serialBuffer = "";
    parsed_data = "";
    temperature_value = 0.0;

    /*
     *  Testing code, prints the description, vendor id, and product id of all ports.
     *  Used it to determine the values for the arduino uno.
     *
     *
    qDebug() << "Number of ports: " << QSerialPortInfo::availablePorts().length() << "\n";
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        qDebug() << "Description: " << serialPortInfo.description() << "\n";
        qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
        qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
        qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
        qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
    }
    */


    /*
     *   Identify the port the arduino uno is on.
     */
    bool arduino_is_available = false;
    QString arduino_uno_port_name;
    //
    //  For each available serial port
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
        //  check if the serialport has both a product identifier and a vendor identifier
        if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()){
            //  check if the product ID and the vendor ID match those of the arduino uno
            if((serialPortInfo.productIdentifier() == arduino_uno_product_id)
                    && (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id)){
                arduino_is_available = true; //    arduino uno is available on this port
                arduino_uno_port_name = serialPortInfo.portName();
            }
        }
    }

    /*
     *  Open and configure the arduino port if available
     */
    if(arduino_is_available){
        qDebug() << "Found the arduino port...\n";
        arduino->setPortName(arduino_uno_port_name);
        arduino->open(QSerialPort::ReadOnly);
        arduino->setBaudRate(QSerialPort::Baud9600);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setFlowControl(QSerialPort::NoFlowControl);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        QObject::connect(arduino, SIGNAL(readyRead()), this, SLOT(readSerial()));
    }else{
        qDebug() << "Couldn't find the correct port for the arduino.\n";
        QMessageBox::information(this, "Serial Port Error", "Couldn't open serial port to arduino.");
    }
    if(arduino->isOpen()){
        arduino->close(); //    Close the serial port if it's open.
    }
    delete ui;
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

       histo.save("num_cin:"+ui->le_classement->text(),"classement :"+ui->le_Nom->text(),"Nom :"+ui->le_NB_athletes->text(),"NB_athlete :"+ui->le_IP->text());




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

/*void MainWindow::on_pushButton_5_clicked()
{
close();
H = new Historique(this);
H->show();
}*/

void MainWindow::on_pushButton_clicked()
{




    {
      QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                       "/home",
                                                       QFileDialog::ShowDirsOnly
                                                       | QFileDialog::DontResolveSymlinks);
           qDebug()<<dir;
           QPdfWriter pdf(dir+"/PdfVoiture.pdf");                                 QPainter painter(&pdf);
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

                                         painter.drawText(2300,3300,"Nom");
                                         painter.drawText(4300,3300,"IP_adresse");
                                         painter.drawText(6300,3300,"NB_athlete");
                                         painter.drawText(8300,3300,"classement");


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
                                                 QDesktopServices::openUrl(QUrl::fromLocalFile(dir+"/Pdfpays.pdf"));

                                                 painter.end();
                                             }
                                             else
                                             {
                                                  painter.end();
                                             }
    }











}

void MainWindow::on_pushButton_2_clicked()
{
    {
        QFile file ("C:/Users/ZAKARIA/Desktop/hi.txt");
        if (!file.open(QIODevice::ReadOnly))
            QMessageBox::information(0,"info",file.errorString());
        QTextStream in (&file);
        ui->textBrowser->setText(in.readAll());
    }
}







void MainWindow::readSerial()
{
    /*
     * readyRead() doesn't guarantee that the entire message will be received all at once.
     * The message can arrive split into parts.  Need to buffer the serial data and then parse for the temperature value.
     *
     */
    QStringList buffer_split = serialBuffer.split("\xC2\xB0"); //  split the serialBuffer string, parsing with ',' as the separator

    //  Check to see if there less than 3 tokens in buffer_split.
    //  If there are at least 3 then this means there were 2 commas,
    //  means there is a parsed temperature value as the second token (between 2 commas)
    if(buffer_split.length() < 3){
        // no parsed value yet so continue accumulating bytes from serial in the buffer.
        serialData = arduino->readAll();
        serialBuffer = serialBuffer + QString::fromStdString(serialData.toStdString());
        serialData.clear();
    }else{
        // the second element of buffer_split is parsed correctly, update the temperature value on temp_lcdNumber
        serialBuffer = "";
        qDebug() << buffer_split << "\n";
        parsed_data = buffer_split[1];
        temperature_value = parsed_data.toDouble() ; // convert to fahrenheit
        qDebug() << "Temperature: " << temperature_value << "\n";
       // parsed_data = QString::number(temperature_value, 'g', 4); // format precision of temperature_value to 4 digits or fewer
        MainWindow::updateTemperature(parsed_data);
    }

}

void MainWindow::updateTemperature(QString sensor_reading)
{
    //  update the value displayed on the lcdNumber
    ui->temp_lcdNumber->display(sensor_reading);
}

































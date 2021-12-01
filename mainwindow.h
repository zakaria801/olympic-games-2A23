#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "historique.h"
#include "history.h"
#include <QMainWindow>
#include "pays.h"
#include <QSerialPort>
#include <QByteArray>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_rech_clicked();


    void on_cb_trie_activated(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void readSerial();
    void updateTemperature(QString);



private:
    Ui::MainWindow *ui;
    pays p;
    //Historique *H;
  historique1 histo;


  QSerialPort *arduino;
  static const quint16 arduino_uno_vendor_id = 9025;
  static const quint16 arduino_uno_product_id = 67;
  QByteArray serialData;
  QString serialBuffer;
  QString parsed_data;
  double temperature_value;




};

#endif // MAINWINDOW_H

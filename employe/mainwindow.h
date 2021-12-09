#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "employe.h"
#include "arduino.h"
#include "qcustomplot.h"
#include <QtMultimedia/QMediaPlayer>
#include <QFileDialog>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
 void makePolt();
private slots:
    void on_pushButton_2_clicked();

    void on_supp_clicked();

    void on_modifer_clicked();

    void on_chercher_clicked();

    void on_pushButton_5_clicked();

    void on_tri_clicked();



    void on_pushButton_6_clicked();


    void on_ajout_conge_clicked();

    void on_line_chercher_textChanged(const QString &arg1);
    void sendMail();
    void mailSent(QString);
    void browse();
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_commandLinkButton_clicked();

    void update_label();


private:
    Ui::MainWindow *ui;
    employe E;
    arduino a;
    QByteArray data;
    QMediaPlayer *player = new QMediaPlayer;
     QStringList files;
};
#endif // MAINWINDOW_H

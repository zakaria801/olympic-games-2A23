#ifndef LOGIN_H
#define LOGIN_H
#include <QtSql>
#include <QFileInfo>
#include <QDialog>
#include <QMessageBox>
#include"admin.h"
#include "mainwindow.h"

#include <QMainWindow>

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pb_login_clicked();

    void on_pb_reset_clicked();

private:
    Ui::Login *ui;

    Admin A;
    MainWindow *M;
};

#endif // LOGIN_H

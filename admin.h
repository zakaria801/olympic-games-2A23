#ifndef ADMIN_H
#define ADMIN_H

#include<QString>
#include<QSqlQueryModel>
#include <QDebug>
#include <QtDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QThread>
class Admin
{
public:
    Admin();
       Admin(QString,QString,QString);
       bool Login();
       QString afficherRole();


   private:
       int id;
       QString username,password,role;
};

#endif // ADMIN_H

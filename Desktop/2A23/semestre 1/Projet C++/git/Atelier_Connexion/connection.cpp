#include "connection.h"
//test tuto git


Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test-bd");//inserer le nom de la source de données ODBC
db.setUserName("achrefneji");//inserer nom de l'utilisateur
db.setPassword("Azerty10.");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
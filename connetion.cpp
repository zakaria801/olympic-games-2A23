#include "Connetion.h"

Connetion::Connetion()
{

}

bool Connetion::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("");//inserer le nom de la source de données ODBC
db.setUserName("");//inserer nom de l'utilisateur
db.setPassword("");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}

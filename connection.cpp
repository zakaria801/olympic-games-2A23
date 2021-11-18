#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{

   QSqlDatabase     db=QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("test-bd");//inserer le nom de la source de données ODBC
db.setUserName("baha");//inserer nom de l'utilisateur
db.setPassword("baha");//inserer mot de passe de cet utilisateur

if (db.open())
return true;
return false;






}

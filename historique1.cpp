#include "historique1.h"
#include <QString>

historique1::historique1()
{

}
void historique1::save(QString ip_adresse, QString Nom, QString nb_athlete, QString classement)
{    QFile file ("C:/Users/ZAKARIA/Desktop/hi.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";

     QTextStream out(&file);
     out << ip_adresse+"\n"+Nom << "\n"+nb_athlete << "\n"+classement<<"\n""------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n";


}
QString historique1::load()
{   tmp="";
    QFile file("C:/Users/ZAKARIA/Desktop/hi.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {

         QString myString = in.readLine();
         tmp+=myString+"\n";

   }
   return tmp;
}

















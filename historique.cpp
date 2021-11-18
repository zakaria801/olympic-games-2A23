#include "historique.h"

historique::historique()
{

}
void historique::save(QString num_cin,QString nom, QString prenom, QString sexe, QString type_event)
{    QFile file ("C:/Users/21651/Desktop/his.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";

     QTextStream out(&file);
     out <<"\n" +num_cin<< "\n"+nom << "\n"+prenom << "\n"+sexe << "\n"+type_event  << "\n""------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n";


}
QString historique::load()
{   tmp="";
    QFile file("C:/Users/21651/Desktop/his.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      tmp="";

    QTextStream in(&file);

   while (!in.atEnd()) {

         QString myString = in.readLine();
         tmp+=myString+"\n";

   }
   return tmp;
}

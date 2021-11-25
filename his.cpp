/*#include "his.h"



his::his()
{

}


void his::save(QString Nom    ,QString IP_adresse, int classement, int NB_athlete)
{    QFile file ("C:/Users/21651/Desktop/his.txt");
     if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text))
      qDebug()<<"erreur";

     QTextStream out(&file);
     out <<"\n" +Nom<< "\n"+IP_adresse << "\n"+ << "\n"+classement << "\n"+NB_athlete  << "\n""------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << "\n";


}
QString his::load()
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
*/

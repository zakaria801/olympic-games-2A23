/*#include "history.h"

history::history()
{
 numero=nb_victoire=0;
 Nom=Description="";
}

history::history(int numero,QString Nom,int nb_victoire,QString Description)
{
    this->numero=numero;
    this->Nom=Nom;
    this->nb_victoire=nb_victoire;
    this->Description=Description;
}

QSqlQueryModel* history::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();


  model->setQuery("SELECT* FROM history");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("numero"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("nb_victoire"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));


  return model;
}

//recherche par nom pays
QSqlQueryModel * history::afficher_recherche1(QString b)
{
    QSqlQueryModel * model =new QSqlQueryModel();

    model->setQuery("SELECT * FROM history where Nom='"+b+"' ");

    return model ;

}


//trie par nom pays alphabétique et par nombre de victoire
QSqlQueryModel *history:: afficher_choix(QString choix)
{
    QSqlQueryModel * model =new QSqlQueryModel();

     if(choix=="NOMBRE VICTOIRE CROISSANT")
    {
        model->setQuery("SELECT * FROM HISTORY  ORDER BY nb_victoire ASC ;");
    }
    else if(choix=="NOMBRE VICTOIRE DECROISSANT")
    {
        model->setQuery("SELECT * FROM HISTORY  ORDER BY nb_victoire DESC ;");
    }
     else if(choix=="NOM CROISSANT")
     {
         model->setQuery("SELECT * FROM HISTORY  ORDER BY NOM ASC ;");
     }
     else if(choix=="NOM DECROISSANT")
     {
         model->setQuery("SELECT * FROM HISTORY  ORDER BY NOM DESC ;");
     }
    else if (choix=="choisir")
    {
        model->setQuery("SELECT * FROM history ");
    }
    return model;

}

*/


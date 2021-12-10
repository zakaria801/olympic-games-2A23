#include "pays.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
pays::pays()
{
    classement=0; Nom=""; NB_athletes=0; IP_adresse="";

}
pays::pays(int classement,QString IP_adresse,QString Nom,int NB_athletes)
{this->classement=classement; this->IP_adresse=IP_adresse; this->Nom=Nom; this->NB_athletes=NB_athletes; }
QString pays::getIP_adresse(){return IP_adresse;}
QString pays::getNom(){return  Nom;}
int pays::getNB_athletes(){return  NB_athletes;}
int pays::getclassement(){return  classement;}
void pays::setIP_adresse(QString IP_adresse){this->IP_adresse=IP_adresse;}
void pays::setNom(QString Nom){this->Nom=Nom;}
void pays::setNB_athletes(int NB_athletes){this->NB_athletes=NB_athletes;}
void pays::setclassement(int classement){this->classement=classement;}

bool pays::ajouter()
{
    QSqlQuery query;
    QString classement_string= QString::number(classement);
    QString NB_athletes_string= QString::number(NB_athletes);
    query.prepare("INSERT INTO pays (NB_athlete,Nom,IP_adresse,classement) "
                  "VALUES (:NB_athletes, :forename, :surname, :classement)");
    query.bindValue(":classement", classement_string);
    query.bindValue(":forename", Nom);
    query.bindValue(":surname", IP_adresse);
    query.bindValue(":NB_athletes",NB_athletes_string );
    return query.exec();
}

QSqlQueryModel* pays::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();


  model->setQuery("SELECT* FROM pays");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("IP_adresse"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("NB_athletes"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("classement"));


  return model;
}

bool pays::supprimer(QString IP_adresse)
{
    QSqlQuery query;
    query.prepare("Delete from pays where IP_adresse= :IP_adresse");
    query.bindValue(0, IP_adresse);
    return query.exec();

}

bool pays::modifier()
{
QSqlQuery query;
QString classement_string= QString::number(classement);
QString NB_athletes_string= QString::number(NB_athletes);
query.prepare("UPDATE pays SET  Nom=:Nom , NB_athlete=:NB_athletes, classement=:classement  WHERE IP_ADRESSE=:IP_ADRESSE");
query.bindValue(":IP_ADRESSE", IP_adresse);
query.bindValue(":Nom", Nom);
query.bindValue(":NB_athletes", NB_athletes_string);
query.bindValue(":classement",classement_string);
return query.exec();
}


QSqlQueryModel * pays::afficher_recherche1(QString b)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    QString classement_string= QString::number(classement);

    model->setQuery("SELECT * FROM pays where classement='"+b+"' ");

    return model ;

}
QSqlQueryModel * pays::afficher_recherche2(QString b)
{
    QSqlQueryModel * model =new QSqlQueryModel();
    QString NB_athletes_string= QString::number(NB_athletes);

    model->setQuery("SELECT * FROM pays where nb_athlethe='"+b+"' ");

    return model ;

}
QSqlQueryModel * pays::afficher_recherche3(QString b)
{
    QSqlQueryModel * model =new QSqlQueryModel();

    model->setQuery("SELECT * FROM pays where Nom='"+b+"' ");

    return model ;

}
QSqlQueryModel * pays::afficher_recherche4(QString b)
{
    QSqlQueryModel * model =new QSqlQueryModel();

    model->setQuery("SELECT * FROM pays where IP_adresse='"+b+"' ");

    return model ;

}

//trie multicritéres

QSqlQueryModel *pays:: afficher_choix(QString choix)
{
    QSqlQueryModel * model =new QSqlQueryModel();

     if(choix=="IP_ADRESSE CROISSANT")
    {
        model->setQuery("SELECT * FROM pays  ORDER BY IP_ADRESSE ASC ;");
    }
    else if(choix=="IP_ADRESSE DECROISSANT")
    {
        model->setQuery("SELECT * FROM pays  ORDER BY IP_ADRESSE DESC ;");
    }
     else if(choix=="NOM CROISSANT")
     {
         model->setQuery("SELECT * FROM pays  ORDER BY NOM ASC ;");
     }
     else if(choix=="NOM DECROISSANT")
     {
         model->setQuery("SELECT * FROM pays  ORDER BY NOM DESC;");
     }else if(choix=="CLASSEMENT CROISSANT")
     {
         model->setQuery("SELECT * FROM pays  ORDER BY CLASSEMENT DESC ;");
     }
     else if(choix=="CLASSEMENT DECROISSANT")
     {
         model->setQuery("SELECT * FROM pays  ORDER BY CLASSEMENT ASC;");
     }
     else if(choix=="NB_ATHLETE CROISSANT")
     {
         model->setQuery("SELECT * FROM pays  ORDER BY NB_ATHLETE DESC ;");
     }
     else if(choix=="NB_ATHLETE DECROISSANT")
     {
         model->setQuery("SELECT * FROM pays  ORDER BY NB_ATHLETE ASC;");
     }
    else if (choix=="choisir")
    {
        model->setQuery("SELECT * FROM pays ");
    }


    return model;



}









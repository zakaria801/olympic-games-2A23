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
    query.prepare("INSERT INTO pays (NB_athléte,Nom,IP_adresse,classement) "
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

bool pays::modifier(QString IP_adresse)
{
QSqlQuery query;
QString classement_string= QString::number(classement);
QString NB_athletes_string= QString::number(NB_athletes);
query.prepare("Update Pays set IP_ADRESSE =:ip_adresse , NOM =:nom , NB_athéte =:nb_athléte,CLASSEMENT =:classement  where IP_ADRESSE =:ip_adresse");
query.bindValue(":ip_adresse", IP_adresse);
query.bindValue(":nom", Nom);
query.bindValue(":classement",classement_string);
query.bindValue(":nb_athléte", NB_athletes_string);
return    query.exec();
}












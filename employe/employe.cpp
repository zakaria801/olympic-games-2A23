#include "employe.h"
#include <QString >
#include<QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
employe::employe()
{
id=0;
nom="";
prenom="";
date="";
 salaire=0;

}

employe::employe(int id ,QString nom ,QString prenom , QString date,int salaire, QString role ){
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->date=date;
    this->salaire= salaire;
    this->role= role;

}

void employe::set_id(int id){this->id=id;}
void employe::set_nom(QString nom){this->nom=nom;}
void employe::set_prenom(QString prenom){ this->prenom=prenom;}
void employe:: set_date(QString date){this->date=date;}
void employe::set_salaire(int salaire){ this->salaire=salaire;}


int employe::get_id(){return id;}
int employe:: get_salaire(){return salaire;}
QString employe:: get_nom(){return nom;}
QString employe:: get_prenom(){return prenom;}
QString employe:: get_date(){return date;}

bool employe::ajouterConges(QString dateC,int idE)
{
    QSqlQuery q;
    q.prepare("insert into conge VALUES(:dateC,:idE)");
    q.bindValue(":dateC",dateC);
    q.bindValue(":idE",idE);


    return q.exec();

}

bool employe::ajouter(){

    QSqlQuery query;
         QString id_string= QString::number(id);
     QString salaire_string= QString::number(salaire);
     query.prepare("INSERT INTO employe (identifiant_e,nom_e,prenom_e,date_e,salaire,role) "
                   "VALUES (:identifiant_e, :nom_e, :prenom_e, :date_e,:salaire, :role)");
     query.bindValue(":identifiant_e", id_string);
     query.bindValue(":nom_e", nom);
     query.bindValue(":prenom_e", prenom);
     query.bindValue(":date_e", date);
     query.bindValue(":salaire",salaire_string );
     query.bindValue(":role",role);
     return query.exec();
}

bool employe::supprimer(int id){
    QSqlQuery query;


            query.prepare("delete from employe where identifiant_e=:iden");
            query.bindValue(0, id);
            return query.exec();

}





QSqlQueryModel* employe::afficher()
{  QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from employe");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire"));
     model->setHeaderData(5, Qt::Horizontal, QObject::tr("role"));

    return model ;
}

bool employe::modifier(int id){

    QSqlQuery query;
    QString id_string= QString::number(id);
    QString salaire_string= QString::number(salaire);
    query.prepare("UPDATE employe SET identifiant_e =:iden, nom_e =:nom , prenom_e =:prenom ,date_e =:date ,salaire =:salaire,role=:role WHERE identifiant_e =:iden ");


    query.bindValue(":iden", id_string);
    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":date", date);
    query.bindValue(":salaire",salaire_string);
    query.bindValue(":role",role);


    return    query.exec();

}


bool employe::rechercher_e (int id )
{
    QSqlQuery q;
    q.prepare ("select id from employe where identifant_e=:id") ;
    q.bindValue(":id",id);
    q.exec();
    return q.next();
}




QSqlQueryModel * employe::afficher_rech(QString recherche){

    QSqlQueryModel * model = new QSqlQueryModel();

    model->setQuery("select * from employe where identifiant_e like '"+recherche+"%' or nom_e like '"+recherche+"%' or prenom_e like '"+recherche+"%' ");
    return model;
}



QSqlQueryModel * employe:: tri(){
 QSqlQueryModel * model= new QSqlQueryModel();

  model->setQuery("select * from employe order by salaire asc");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("role"));
  return model ;
}



QSqlQueryModel * employe :: tri1(){
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from employe order by identifiant_e asc  ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire"));
     model->setHeaderData(4, Qt::Horizontal, QObject::tr("role"));

    return model ;
}


QSqlQueryModel * employe :: tri2(){

    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from employe order by date_e asc  ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("salaire"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("role"));
    return model ;
}



QSqlQueryModel *employe::rechercherid(QString q)
{

     QSqlQueryModel *model=new QSqlQueryModel();
      model->setQuery("SELECT * FROM employe  WHERE identifiant_e like '"+q+"%'  or prenom_e like '"+q+"%' ");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("Identifiant"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Salaire"));
      model->setHeaderData(4, Qt::Horizontal, QObject::tr("role"));

      return model;
}

QSqlQueryModel * employe::stat()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select role,count(*) as nombre from employe group by role");
    return model ;
}


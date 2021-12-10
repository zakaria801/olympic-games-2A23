#include "athlete.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
Athlete::Athlete()
{
    num_cin=0;nom_a=" ";prenom_a=" ";sexe=" ";type_event="";
}
Athlete::Athlete(int num_cin,QString nom_a ,QString prenom_a ,QString  sexe,QString type_event)
    {this->num_cin=num_cin;this->nom_a=nom_a;this->prenom_a=prenom_a;this->sexe=sexe;this->type_event=type_event;}
int Athlete::getnum_cin(){return num_cin;}
QString Athlete::getnom_a(){return nom_a;}
QString Athlete::getprenom_a (){return prenom_a;}
QString Athlete::getsexe (){return sexe;}
QString Athlete::gettype_event(){return type_event;}

void Athlete::setnum_cin (int num_cin){this->num_cin=num_cin;}
void Athlete::setnom_a (QString nom_a){this->nom_a=nom_a;}
void Athlete::setprenom_a(QString prenom_a) {this->prenom_a=prenom_a;}
void Athlete::setsexe(QString sexe){this->sexe=sexe;}
void Athlete::settype_event(QString type_event){this->type_event=type_event;}

bool Athlete::ajouter()
{
    QSqlQuery query;
    QString num_cin_string =QString::number(num_cin);


         query.prepare("INSERT INTO athlete (num_cin,nom_a,prenom_a,sexe,type_event ) "
                       "VALUES (:num_cin, :nom_a, :prenom_a, :sexe, :type_event)");
         query.bindValue(":num_cin", num_cin_string);
         query.bindValue(":nom_a", nom_a);
         query.bindValue(":prenom_a", prenom_a);
         query.bindValue(":sexe", sexe);
         query.bindValue(":type_event", type_event);


         return query.exec();


}



bool Athlete::supprimer(int num_cin){
     QSqlQuery query;
    query.prepare("Delete from athlete where num_cin=:num_cin");

    query.bindValue(":num_cin",num_cin);

    return query.exec();

}

QSqlQueryModel* Athlete::afficher(){
QSqlQueryModel* model=new QSqlQueryModel();
model->setQuery("SELECT* FROM athlete");
      model->setHeaderData(0, Qt::Horizontal, QObject::tr("NUM CIN"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom_a"));
       model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom_a"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("sexe"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("type_event"));




return model;

}


bool Athlete::modifier(int num_cin)
{
QSqlQuery query;
QString res= QString::number(num_cin);
query.prepare("Update athlete set num_cin = :num_cin , nom_a = :nom_a , prenom_a = :prenom_a , sexe =sexe , type_event = :type_event  where num_cin = :num_cin ");
query.bindValue(":num_cin", res);
query.bindValue(":nom_a", nom_a);
query.bindValue(":prenom_a", prenom_a);
query.bindValue(":sexe", sexe);
query.bindValue(":type_event", type_event);
return    query.exec();
}











QSqlQueryModel * Athlete::tri()
{
QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM athlete ORDER BY CAST(num_cin AS number)");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("num_cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("sexe"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("type_event"));


    return model;
}
QSqlQueryModel * Athlete::tri1()
{
QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM athlete ORDER BY nom_a DESC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("num_cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("sexe"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("type_event"));

    return model;
}
QSqlQueryModel * Athlete::tri2()
{
QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("SELECT * FROM athlete ORDER BY  sexe DESC");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("num_cin"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("sexe"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("type_event"));


    return model;
}




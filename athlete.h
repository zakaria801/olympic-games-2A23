#ifndef ATHLETE_H
#define ATHLETE_H
#include<QString>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include "historique.h"


class Athlete
{
public:
    Athlete();
    Athlete(int,QString,QString,QString,QString);

        int getnum_cin();
        QString getnom_a();
        QString getprenom_a ();
        QString getsexe ();
        QString gettype_event();

        void setnum_cin (int);
        void setnom_a (QString);
        void setprenom_a (QString);
        void setsexe(QString);
        void settype_event(QString);

        bool ajouter();
        bool supprimer(int);
         bool modifier(int);
QSqlQueryModel* afficher();
QSqlQueryModel * tri();
     QSqlQueryModel * tri1();
     QSqlQueryModel * tri2();



     private:
            int num_cin ;
        QString nom_a, prenom_a , sexe,type_event;





};

#endif // ATHLETE_H


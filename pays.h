#ifndef PAYS_H
#define PAYS_H

#include <QString>
#include <QSqlQueryModel>
#include "historique1.h"
class pays
{
public:
    pays();
    pays(int,QString,QString,int);
    QString getIP_adresse();
    QString getNom();
    int getNB_athletes();
    int getclassement();
    void setIP_adresse(QString);
    void setNom(QString);
    void setNB_athletes(int);
    void setclassement(int);
    bool ajouter();
   QSqlQueryModel* afficher();
   bool supprimer(QString);
   bool modifier();
   QSqlQueryModel * afficher_recherche1(QString b);
   QSqlQueryModel * afficher_recherche2(QString b);
   QSqlQueryModel * afficher_recherche3(QString b);
   QSqlQueryModel * afficher_recherche4(QString b);
   QSqlQueryModel* afficher_choix(QString choix);


 private:
 QString IP_adresse;
 QString Nom;
 int NB_athletes;
 int classement;
};

#endif // PAYS_H
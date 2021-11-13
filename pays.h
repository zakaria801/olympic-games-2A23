#ifndef PAYS_H
#define PAYS_H

#include <QString>
#include <QSqlQueryModel>
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
   bool modifier(QString);


 private:
 QString IP_adresse;
 QString Nom;
 int NB_athletes;
 int classement;
};

#endif // PAYS_H

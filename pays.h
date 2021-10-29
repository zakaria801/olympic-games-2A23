#ifndef PAYS_H
#define PAYS_H

#include <QString>
class pays
{
public:
    pays();
    pays(int,QString,QString,QString);
    QString getIP_adresse();
    QString getNom();
    QString getcontinent();
    int getclassement();
    void setIP_adresse(QString);
    void setNom(QString);
    void setcontinent(QString);
    void setclassement(int);
    bool ajouter();

 private:
 QString IP_adresse;
 QString Nom;
 QString continent;
 int classement;
};

#endif // PAYS_H

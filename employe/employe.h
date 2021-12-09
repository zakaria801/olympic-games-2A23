#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString >
#include<QSqlQuery>
#include<QVariant>
#include <QSqlQueryModel>

class employe
{
public:
    employe();
    employe(int,QString,QString,QString,int,QString);
    int get_id();
    int get_salaire();
    QString get_nom();
    QString get_prenom();
    QString get_date();
QSqlQueryModel * rechercherid(QString q);
    void set_id(int);
    void set_nom(QString);
    void set_prenom(QString);
    void set_date(QString);
    void set_salaire(int);
    bool ajouterConges(QString,int);

    QSqlQueryModel* afficherC();
    bool ajouter();
    bool supprimer(int);
   QSqlQueryModel* afficher();
   bool modifier(int);
   bool rechercher_e(int);
   QSqlQueryModel* afficher_rech(QString);
   QSqlQueryModel * tri();
   QSqlQueryModel * tri1();
    QSqlQueryModel * tri2();
    QSqlQueryModel * stat();


private:
    int id;
    QString nom;
    QString prenom;
    QString date;
    int salaire;
    QString role;
    
};

#endif // EMPLOYE_H

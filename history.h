#ifndef HISTORY_H
#define HISTORY_H
#include <QString>
#include <QSqlQueryModel>

class history
{
public:
    history();
    history(int,QString,int,QString);
    int getNum(){return numero ;}
    int getNbVictoire(){return nb_victoire;}
    QString getNom(){return Nom;}
    QString getDescription(){return Description;}
    void setNum(int Numero){this->numero=numero;}
    void setNbVictoire(int nb_victoire){this->nb_victoire=nb_victoire;}
    void setNom(QString Nom){this->Nom=Nom;}
    void setDescription(QString Description){this->Description=Description;}





   QSqlQueryModel* afficher();

   QSqlQueryModel * afficher_recherche1(QString b);

   QSqlQueryModel * afficher_choix(QString choix);






private:
   int numero, nb_victoire;
   QString Nom,Description;


};

#endif // HISTORY_H

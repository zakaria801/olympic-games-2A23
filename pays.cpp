#include "pays.h"
pays::pays()
{
    classement=0; Nom=""; continent=""; IP_adresse="";

}
pays::pays(int classement,QString IP_adresse,QString Nom,QString continent)
{this->classement=classement; this->IP_adresse=IP_adresse; this->Nom=Nom; this->continent=continent; }
QString pays::getIP_adresse(){return IP_adresse;}
QString pays::getNom(){return  Nom;}
QString pays::getcontinent(){return  continent;}
int pays::getclassement(){return  classement;}
void pays::setIP_adresse(QString IP_adresse){this->IP_adresse=IP_adresse;}
void pays::setNom(QString Nom){this->Nom=Nom;}
void pays::setcontinent(QString continent){this->continent=continent;}
void pays::setclassement(int classement){this->classement=classement;}
bool pays::ajouter()
{bool test=false;


    return test;
}



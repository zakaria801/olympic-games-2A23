/*#include "historique.h"
#include "ui_historique.h"


Historique::Historique(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Historique)
{
    ui->setupUi(this);
    ui->tab_his->setModel(H.afficher());
}

Historique::~Historique()
{
    delete ui;
}


void Historique::on_le_act_clicked()
{
    ui->tab_his->setModel(H.afficher());
}

void Historique::on_pb_quitter_clicked()
{
    close();
}

void Historique::on_rech_clicked()
{
    QString val=ui->le_rech->text();
    ui->tab_his->setModel(H.afficher_recherche1(val));
}



void Historique::on_cb_trie_his_activated(const QString &arg1)
{
    QString choix=ui->cb_trie_his->currentText();
    ui->tab_his->setModel(H.afficher_choix(choix));
}
*/

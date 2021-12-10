/*#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include "history.h"
#include <QMainWindow>
#include <QMessageBox>
#include <QIntValidator>
#include <QtDebug>
namespace Ui {
class Historique;
}

class Historique : public QMainWindow
{
    Q_OBJECT

public:
    explicit Historique(QWidget *parent = nullptr);
    ~Historique();

private slots:
    void on_le_act_clicked();

    void on_pb_quitter_clicked();

    void on_rech_clicked();


    void on_cb_trie_his_activated(const QString &arg1);

private:
    Ui::Historique *ui;
    history H;
};

#endif // HISTORIQUE_H
*/

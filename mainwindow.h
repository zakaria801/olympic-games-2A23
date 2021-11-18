#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "historique.h"
#include "history.h"
#include <QMainWindow>
#include "pays.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_rech_clicked();


    void on_cb_trie_activated(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_pushButton_clicked();
    void on_puhButton_pdf_clicked();

private:
    Ui::MainWindow *ui;
    pays p;
    Historique *H;

};

#endif // MAINWINDOW_H

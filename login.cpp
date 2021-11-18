#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
    delete M;
}


void Login::on_pb_login_clicked()
{

    QString Username, Password , role;
   Username =ui->le_username->text();
    Password=ui->le_password->text();
 Admin A1(Username,Password,role);
 ui->role->setText(A1.afficherRole());
 QString RecupRole=ui->role->text();
 qDebug()<<RecupRole;
 bool test=A1.Login();
 if(test)
   {
     ui->role->setText(A1.afficherRole());
     RecupRole=ui->role->text();
     ui->label_3->setText("[+]Valid username and password ");
     if(RecupRole=="admin")
     {
         close();
         M= new MainWindow(this);
         M->show();

     }


    }
 else {
       ui->label_3->setText("wrong username or password");
      }


}

void Login::on_pb_reset_clicked()
{
    ui->le_password->setText("");
        ui->le_username->setText("");
}

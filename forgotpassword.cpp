#include "forgotpassword.h"
#include "ui_forgotpassword.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
#include"loginpage.h"


forgotPassword::forgotPassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forgotPassword)
{
    ui->setupUi(this);
}

forgotPassword::~forgotPassword()
{
    delete ui;
}

void forgotPassword::on_update_PushButton_clicked()
{
    QString username = ui->username_lineEdit->text() ;
    QString newpw = ui->newPassword_lineEdit->text();


    QString checkUser, checkComp;

    QSqlDatabase db01 = QSqlDatabase::addDatabase("QSQLITE");

    db01.setDatabaseName("C:/Users/PC/OneDrive/Desktop/tryingDB/Companies.db");
   if ( db01.open())
   {
       QSqlQuery qry , qrycomp;


       qry.prepare("select * from USER where username=:username");
       qry.bindValue(":username" ,username);

        if(qry.exec())
              {
                  while(qry.next())
                  {

                      checkUser = qry.value(2).toString() ;

                    }
           }
        if( checkUser == username)
        {
            QSqlQuery updatePw ;
            updatePw.prepare("UPDATE USER SET password = '"+newpw+"' WHERE username = '"+username+"'");
            updatePw.bindValue(":password", newpw);
            if( updatePw.exec()){
             QMessageBox::information(this,"","Password Successfully Updated");  }
             db01.close();

             loginpage pp ;
             this->close();
             pp.exec();

        }

        qrycomp.prepare("select * from COMPANY where username=:username");
        qrycomp.bindValue(":username" ,username);

         if(qrycomp.exec())
               {
                   while(qrycomp.next())
                   {

                       checkComp = qrycomp.value(4).toString() ;

                     }
            }
         if( checkComp == username)
         {
             QSqlQuery updatePw ;
             updatePw.prepare("UPDATE COMPANY SET password = '"+newpw+"' WHERE username = '"+username+"'");
             updatePw.bindValue(":password", newpw);
             if( updatePw.exec()){
              QMessageBox::information(this,"","Password Successfully Updated");  }
              db01.close();

              loginpage pp ;
              this->close();
              pp.exec();

         }
    }

}

void forgotPassword::on_back_clicked()
{
    loginpage back ;
    hide() ;
    back.exec();
}


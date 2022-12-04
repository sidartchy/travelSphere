#include "profile.h"
#include "ui_profile.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
#include"mainwindow.h"
#include"loginpage.h"
#include"profile.h"

extern QString username ;
profile::profile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::profile)
{
    ui->setupUi(this);
    ui->lineEdit_name->hide();
    ui->dob_dateEdit->hide();

    ui->lineEdit_pwold->hide();
    ui->newPW_lineEdit->hide();
    ui->pushButton_update->hide();
    ui->icon_passwordnew->hide();
    ui->icon_passwordold->hide() ;
     ui->updatePW_pushbutton->hide();
    ui->icon_plan->hide();
    ui->icon_departureDate->hide();
    ui->cancel_book->hide();
    ui->label_departDate->hide();
    ui->label_plan->hide();

    QSqlDatabase db01 = QSqlDatabase::addDatabase("QSQLITE");

    db01.setDatabaseName("C:/Users/PC/OneDrive/Desktop/tryingDB/Companies.db");
    db01.open();
    QSqlQuery qry ;


    qry.prepare("select * from USER where username=:username");
    qry.bindValue(":username" ,username);

           if(qry.exec())
           {
               while(qry.next())
               {
                   ui->nam_label->setText(qry.value(0).toString());
                   ui->dob_label->setText(qry.value(5).toString());
                   ui->emaillabel->setText(qry.value(1).toString());
                   ui->company_label->setText(qry.value(7).toString());

                 }
        }

           db01.close();


}

profile::~profile()
{
    delete ui;
}

void profile::on_edit_profie_clicked()
{
    ui->edit_profie->hide();
    ui->pushButton_update->show();

    QSqlDatabase db01 = QSqlDatabase::addDatabase("QSQLITE");

    db01.setDatabaseName("C:/Users/PC/OneDrive/Desktop/tryingDB/Companies.db");
    db01.open();
    QSqlQuery qry ;


    qry.prepare("select * from USER where username=:username");
    qry.bindValue(":username" ,username);

           if(qry.exec())
           {
               while(qry.next())
               {

                     ui->lineEdit_name->show();
                     ui->dob_dateEdit->show();


                    ui->lineEdit_name->setText(qry.value(0).toString()) ;



                }
            }


}


void profile::on_pushButton_update_clicked()
{
    QSqlDatabase db01 = QSqlDatabase::addDatabase("QSQLITE");

     db01.setDatabaseName("C:/Users/PC/OneDrive/Desktop/tryingDB/Companies.db");


   QString fullName = ui->lineEdit_name->text();


     QString DoB = ui->dob_dateEdit->text();







     //opening databsaae
       db01.open();
       QSqlQuery aa;
         //preparing and binding the values
      QString updateQuery = "UPDATE USER SET FullName = '"+fullName+"', DOB='"+DoB+"' WHERE username = '"+username+"' " ;
         aa.prepare(updateQuery);

        aa.bindValue(":FullName",fullName);


        aa.bindValue(":DOB", DoB);


        if( aa.exec()){
         QMessageBox::information(this,"","Information Successfully Updated");  }
         db01.close();

         profile pp ;
         this->close();
         pp.exec();
}


void profile::on_back_clicked()
{
    MainWindow *mw = new MainWindow();
    this->close();
    mw->show();

}


void profile::on_changePW_PushButton_clicked()
{
    ui->newPW_lineEdit->show();
    ui->lineEdit_pwold->show();
    ui->icon_passwordnew->show();
    ui->icon_passwordold->show();
    ui->updatePW_pushbutton->show();

}


void profile::on_updatePW_pushbutton_clicked()
{
    QString checkOld, newpass ;
    newpass = ui->newPW_lineEdit->text();
    checkOld = ui->lineEdit_pwold->text() ;
    QString oldpass ;


    QSqlDatabase db01 = QSqlDatabase::addDatabase("QSQLITE");

    db01.setDatabaseName("C:/Users/PC/OneDrive/Desktop/tryingDB/Companies.db");
   if ( db01.open())
   {
       QSqlQuery qry ;


       qry.prepare("select * from USER where username=:username");
       qry.bindValue(":username" ,username);

        if(qry.exec())
              {
                  while(qry.next())
                  {

                      oldpass = qry.value(3).toString() ;

                    }
           }
        if( oldpass == checkOld)
        {
            QSqlQuery updatePw ;
            updatePw.prepare("UPDATE USER SET password = '"+newpass+"' WHERE username = '"+username+"'");
            updatePw.bindValue(":password", newpass);
            if( updatePw.exec()){
             QMessageBox::information(this,"","Password Successfully Updated");  }
             db01.close();

             profile pp ;
             this->close();
             pp.exec();

        }



   }


}


void profile::on_pushButton_clicked()
{
    loginpage log ;
    hide() ;
    log.exec() ;
}


void profile::on_seePlans_clicked()
{
    ui->icon_plan->show();
    ui->icon_departureDate->show();

    ui->cancel_book->show();

    QSqlDatabase db01 = QSqlDatabase::addDatabase("QSQLITE");

    db01.setDatabaseName("C:/Users/PC/OneDrive/Desktop/tryingDB/Companies.db");
    db01.open();
    QSqlQuery qry ;


    qry.prepare("select * from BOOKINGS where Customers_Name=:username");
    qry.bindValue(":username" ,username);

           if(qry.exec())
           {
               while(qry.next())
               {
                   ui->label_departDate->setText(qry.value(3).toString());
                   ui->label_plan->setText("From: "+qry.value(1).toString()+ " To: "+qry.value(2).toString());
                   ui->label_departDate->show();
                   ui->label_plan->show();


                 }
        }

           db01.close();


}


void profile::on_cancel_book_clicked()
{

    QSqlDatabase db01=QSqlDatabase::addDatabase("QSQLITE");
    db01.setDatabaseName("C:/Users/PC/OneDrive/Desktop/tryingDB/Companies.db");


    if(db01.open())
    {
      // QString customerUserName =  ui->lineEdit_CustomerUserName->text() ;
        QSqlQuery aa , updateUser;
        aa.prepare("DELETE FROM BOOKINGS WHERE Customers_Name='"+username+"'  ") ;
        updateUser.prepare("UPDATE USER SET company_username= NULL WHERE username = '"+username+"'") ;
        if(aa.exec())
        {
            //updateUser.bindValue(":complany_username")
            updateUser.exec();


            QMessageBox::information(this, "", "Order Canceled Successfully") ;
            this->close();
            profile refresh;
            refresh.exec();

        }
        db01.close();

}

}

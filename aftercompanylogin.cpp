#include "aftercompanylogin.h"
#include "ui_aftercompanylogin.h"
#include<QtSql>
#include<QMessageBox>
#include"loginpage.h"
#include<QSqlDatabase>
extern QString username ;

AfterCompanyLogin::AfterCompanyLogin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AfterCompanyLogin)
{
    ui->setupUi(this);
    ui->list_label->hide() ;
    ui->companyUsername->setText(username)  ;
    ui->icon_customerUserName->hide();
    ui->lineEdit_CustomerUserName->hide() ;
    ui->cancel_order->hide();
    ui->oldPassword->hide();
    ui->new_password->hide();




  /*
   * Room for improvement
   * Declare database in login page and create functions to open and close
   * using the object of login page, open and close the db
   *
   * */
    QSqlDatabase db01 = QSqlDatabase::addDatabase("QSQLITE");

    db01.setDatabaseName("C:/Users/PC/OneDrive/Desktop/tryingDB/Companies.db");
    db01.open();
    QSqlQuery qry ;



    qry.prepare("select * from COMPANY where username=:username");
    qry.bindValue(":username" ,username);

           if(qry.exec())
           {
               while(qry.next())
               {
                   ui->email_label->setText(qry.value(3).toString());
                   ui->date_label->setText(qry.value(7).toString());
                   ui->phone_number->setText(qry.value(4).toString());

                 }
        }

}

AfterCompanyLogin::~AfterCompanyLogin()
{
    delete ui;
}

void AfterCompanyLogin::on_customers_clicked()
{

    QSqlDatabase db01=QSqlDatabase::addDatabase("QSQLITE");
    db01.setDatabaseName("C:/Users/PC/OneDrive/Desktop/tryingDB/Companies.db");
    ui->list_label->show() ;

    db01.open() ;
    QSqlQueryModel *modal =new QSqlQueryModel();

            QSqlQuery * qry=new QSqlQuery();
            qry->prepare("select * from BOOKINGS  WHERE Company_Username = '"+username+"' ");
            qry->exec();
            modal->setQuery(*qry);
            ui->tableView->setModel(modal);
            qDebug()<<(modal->rowCount());

            db01.close() ;

}


void AfterCompanyLogin::on_signout_clicked()
{
    loginpage log ;
    hide() ;
    log.exec();
}

void AfterCompanyLogin::on_update_clicked()
{
    ui->icon_customerUserName->show();
    ui->lineEdit_CustomerUserName->show() ;
    ui->cancel_order->show() ;

}

void AfterCompanyLogin::on_cancel_order_clicked()
{
    QSqlDatabase db01=QSqlDatabase::addDatabase("QSQLITE");
    db01.setDatabaseName("C:/Users/PC/OneDrive/Desktop/tryingDB/Companies.db");


    if(db01.open())
    {
       QString customerUserName =  ui->lineEdit_CustomerUserName->text() ;
        QSqlQuery aa , updateUser;
        aa.prepare("DELETE FROM BOOKINGS WHERE Customers_Name='"+customerUserName+"'  ") ;
        updateUser.prepare("UPDATE USER SET company_username= NULL WHERE username = '"+customerUserName+"'") ;
        if(aa.exec())
        {
            //updateUser.bindValue(":complany_username")
            updateUser.exec();


            QMessageBox::information(this, "", "Order Canceled Successfully") ;
            this->close();
            AfterCompanyLogin *refresh = new AfterCompanyLogin;
            refresh->show();
        }
        db01.close();

    }

}




void AfterCompanyLogin::on_search_LineEdit_textChanged(const QString &arg1)
{
    QSqlDatabase db01=QSqlDatabase::addDatabase("QSQLITE");
    db01.setDatabaseName("C:/Users/PC/OneDrive/Desktop/tryingDB/Companies.db");



        if(db01.open())
        {
            QString search=ui->search_LineEdit->text();
            QSqlQueryModel *modal =new QSqlQueryModel();

            QSqlQuery * qry=new QSqlQuery();
            qry->prepare("select * from BOOKINGS where Customers_Name like '"+search+"%"+"'  WHERE Company_Username= '"+username+"'");
            qry->bindValue(":search", search);
            qry->exec();
            modal->setQuery(*qry);
            ui->tableView->setModel(modal);
            qDebug()<<(modal->rowCount());
        }





}




void AfterCompanyLogin::on_change_password_clicked()
{
    ui->new_password->show();
    ui->oldPassword->show();
    ui->tableView->hide();
    QString checkOld, newpass ;
    newpass = ui->new_password->text();
    checkOld = ui->oldPassword->text() ;
    QString oldpass ;


    QSqlDatabase db01 = QSqlDatabase::addDatabase("QSQLITE");

    db01.setDatabaseName("C:/Users/PC/OneDrive/Desktop/tryingDB/Companies.db");
   if ( db01.open())
   {


       QSqlQuery qry ;


       qry.prepare("select * from COMPANY where username=:username");
       qry.bindValue(":username" ,username);

        if(qry.exec())
              {
                  while(qry.next())
                  {

                      oldpass = qry.value(5).toString() ;

                    }
           }
        if( oldpass == checkOld)
        {
            QSqlQuery updatePw ;
            updatePw.prepare("UPDATE COMPANY SET password = '"+newpass+"' WHERE username = '"+username+"'");
            updatePw.bindValue(":password", newpass);
            if( updatePw.exec()){
             QMessageBox::information(this,"","Password Successfully Updated");  }
             db01.close();
    }
}

}


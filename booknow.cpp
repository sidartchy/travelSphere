#include "booknow.h"
#include "ui_booknow.h"
#include "contactus.h"
#include "mainwindow.h"
#include<QSql>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QMessageBox>
#include<profile.h>

extern QString username ;



BookNow::BookNow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookNow)
{
    ui->setupUi(this);
 ui->tableView->hide();
    ui->UserName->setText(username);
}

BookNow::~BookNow()
{
    delete ui;
}

void BookNow::on_ContactUs_PushButton_clicked()
{
    ContactUs developersInfo ;
    developersInfo.setModal(true);
    developersInfo.exec() ;


}


void BookNow::on_home_clicked()
{
    this->close();
      MainWindow *home = new MainWindow();
      home->show();

}





void BookNow::on_see_Companies_clicked()
{
    QSqlDatabase db01=QSqlDatabase::addDatabase("QSQLITE");
    db01.setDatabaseName("C:/Users/PC/OneDrive/Desktop/tryingDB/Companies.db");
    ui->tableView->show();

    db01.open() ;
    QSqlQueryModel *modal =new QSqlQueryModel();

            QSqlQuery * qry=new QSqlQuery();
            qry->prepare("select username,Name, Address, Email, Contact from COMPANY");
            qry->exec();
            modal->setQuery(*qry);
            ui->tableView->setModel(modal);
            qDebug()<<(modal->rowCount());








}


void BookNow::on_book_button_clicked()
{


    QSqlDatabase db01 = QSqlDatabase::addDatabase("QSQLITE");

     db01.setDatabaseName("C:/Users/PC/OneDrive/Desktop/tryingDB/Companies.db");

     db01.open();



     QString from = ui->From->text();
     QString to = ui->destination->currentText();

     QDate depart = ui->departDate->date();
     QDate arrive = ui->returnDate->date();

     QString departDate = depart.toString();
     QString arriveDate = arrive.toString();




    QString  company_username = ui->companyName->text();


    QString flagCompany ;

    QSqlQuery checkCompany ;
   int match = 0 ;
    checkCompany.prepare("SELECT * FROM COMPANY WHERE username = '"+company_username+"'");
    {
        if(checkCompany.exec())
        {

            while(checkCompany.next())
            {
                 match++ ;


            }

        }
    }





     //opening databsaae

/*
if( flagCompany == company_username)
{
    match = 1 ;
}*/

if(from != "" && company_username != "")
{


    if(match == 1 )
    {


               QSqlQuery aa ,check, update, updateBooking;

                int user_id = 0;
                if (check.exec("select * from BOOKINGS where Customers_Name ='" + username + "' "))
                 {
                         while (check.next())
                         {
                                 user_id++;
                         }
                 }

                 if (user_id == 1)
                 {
                     QMessageBox::information(this, "Error", "You have already booked from another Company. Cancel First !!.");
                 }




                 else
                 {
                 //preparing and binding the values
                      QString registerQuery = "INSERT INTO BOOKINGS([Customers_Name],[From],[To],[Departure_Date],[Arrival_Date],[Company_Username])VALUES(:name,:from,:to,:depart, :arrive, :companyusername)" ;
                         aa.prepare(registerQuery);

                        aa.bindValue(":name", username);
                        aa.bindValue(":from",from);
                        aa.bindValue(":to", to);
                        aa.bindValue(":depart", departDate);
                        aa.bindValue(":arrive", arriveDate);
                        aa.bindValue(":companyusername", company_username);



      // aa.exec() ;
        if( aa.exec())
        {
            update.prepare("UPDATE USER SET company_username='"+company_username+"' WHERE username = '"+username+"'  ");

            update.exec() ;
           // updateBooking.exec() ;


         QMessageBox::information(this,"","Booking confirmed");
        }


   }

         db01.close();


    }
    else QMessageBox::warning(this, "Not found", "Company Not Found") ;

}

    else QMessageBox::warning(this, "Missing", "Fill up every credentials");
}








void BookNow::on_Profile_PushButton_clicked()
{
    profile prof ;
    hide() ;
    prof.exec() ;
}

void BookNow::on_tableView_activated(const QModelIndex &index)
{

    QString var = ui->tableView->model()->data(index).toString() ;
    QSqlDatabase db01 = QSqlDatabase::addDatabase("QSQLITE");

     db01.setDatabaseName("C:/Users/PC/OneDrive/Desktop/tryingDB/Companies.db");

     db01.open();

     QSqlQuery qrytbl ;
     // QString  company_username = ui->companyName->text();
     qrytbl.prepare("SELECT * FROM COMPANY WHERE username = '"+var+"'") ;
     if(qrytbl.exec())
     {
         while(qrytbl.next())
         {
                 ui->companyName->setText(qrytbl.value(4).toString()) ;
               }

      }



           db01.close() ;
}


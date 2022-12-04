#include "loginpage.h"
#include<mainwindow.h>


#include <QApplication>
#include<QMessageBox>
#include<QtSql>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QSqlRelationalTableModel>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

   loginpage w;


    w.show();
    return a.exec();
}

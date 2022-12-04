#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include"contactus.h"
#include<namobuddha.h>
#include<hazarsidi.h>
#include<chandragiri.h>
#include<pokhara.h>
#include"booknow.h"
#include<profile.h>





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_NamoBuddha_PushButton_clicked()
{
     Namobuddha namobuddha;
     namobuddha.setModal(true);
     namobuddha.exec();
}


void MainWindow::on_Pokhara_PushButton_clicked()
{
    class Pokhara pokhara;
    pokhara.setModal(true);
    pokhara.exec();
}


void MainWindow::on_ThousandStep_PushButton_clicked()
{
    class hazarsidi thousand_step;
    thousand_step.setModal(true);
    thousand_step.exec();
}


void MainWindow::on_Chandragiri_PushButton_clicked()
{
   class chandragiri chandragiri;
    chandragiri.setModal(true);
    chandragiri.exec();
}








void MainWindow::on_bookNow_clicked()
{
    BookNow bn ;
    hide() ;
    bn.exec() ;
}


void MainWindow::on_Profile_clicked()
{
    profile pro ;
    hide() ;
    pro.exec() ;

}




void MainWindow::on_ContactUs_clicked()
{
    ContactUs developersInfo ;
    developersInfo.setModal(true);
    developersInfo.exec() ;
}


#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QDialog>
#include<QtSql>
#include<QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class loginpage; }
QT_END_NAMESPACE

class loginpage : public QDialog
{
    Q_OBJECT

public:
    loginpage(QWidget *parent = nullptr);
    ~loginpage();

private slots:
    void on_login_clicked();

    void on_signUp_clicked();



    void on_forgotPW_clicked();

private:
    Ui::loginpage *ui;
};
#endif // LOGINPAGE_H

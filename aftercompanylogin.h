#ifndef AFTERCOMPANYLOGIN_H
#define AFTERCOMPANYLOGIN_H

#include <QMainWindow>

namespace Ui {
class AfterCompanyLogin;
}

class AfterCompanyLogin : public QMainWindow
{
    Q_OBJECT

public:
    explicit AfterCompanyLogin(QWidget *parent = nullptr);
    ~AfterCompanyLogin();

private slots:


    void on_customers_clicked();

    void on_signout_clicked();

    void on_cancel_order_clicked();

    void on_update_clicked();

    void on_search_LineEdit_textChanged(const QString &arg1);



    void on_change_password_clicked();

private:
    Ui::AfterCompanyLogin *ui;
};

#endif // AFTERCOMPANYLOGIN_H

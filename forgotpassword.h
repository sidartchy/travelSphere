#ifndef FORGOTPASSWORD_H
#define FORGOTPASSWORD_H

#include <QDialog>

namespace Ui {
class forgotPassword;
}

class forgotPassword : public QDialog
{
    Q_OBJECT

public:
    explicit forgotPassword(QWidget *parent = nullptr);
    ~forgotPassword();

private slots:
    void on_update_PushButton_clicked();

    void on_back_clicked();

private:
    Ui::forgotPassword *ui;
};

#endif // FORGOTPASSWORD_H

#ifndef PROFILE_H
#define PROFILE_H

#include <QDialog>

namespace Ui {
class profile;
}

class profile : public QDialog
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = nullptr);
    ~profile();

private slots:
    void on_edit_profie_clicked();

    void on_pushButton_update_clicked();

    void on_back_clicked();

    void on_changePW_PushButton_clicked();

    void on_updatePW_pushbutton_clicked();

    void on_pushButton_clicked();

    void on_seePlans_clicked();

    void on_cancel_book_clicked();

private:
    Ui::profile *ui;
};

#endif // PROFILE_H

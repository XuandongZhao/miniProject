#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_loginb_clicked();

    void on_exitb_clicked();

    void on_signb_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H

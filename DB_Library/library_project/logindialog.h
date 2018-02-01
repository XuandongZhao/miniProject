#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include<QString>
#include <QDialog>
class QCompleter;
namespace Ui {
class logindialog;
}

class logindialog : public QDialog
{
    Q_OBJECT

public:
    explicit logindialog(QWidget *parent = 0);
    ~logindialog();
    QCompleter *completer;

signals:
    void passWordIsRight();
private slots:
    void on_login_button_clicked();

    void on_exit_button_clicked();

private:
    Ui::logindialog *ui;
};

#endif // LOGINDIALOG_H

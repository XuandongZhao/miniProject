#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "logindialog.h"
#include <QFile>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_book_in_clicked();

    void on_book_check_clicked();

    void on_book_borrow_clicked();

    void on_book_return_clicked();

    void on_borrow_card_clicked();

    void on_ad_register_clicked();

private:
    Ui::MainWindow *ui;
    logindialog *mLoginDialog;

};

#endif // MAINWINDOW_H

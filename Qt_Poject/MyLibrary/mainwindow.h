#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
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
    void on_booksearch_clicked();

    void on_bookborrow_clicked();

    void on_bookreturn_clicked();

    void on_card_clicked();

    void on_insertbook_clicked();

    void on_ad_register_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

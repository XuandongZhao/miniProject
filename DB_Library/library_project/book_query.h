#ifndef BOOK_QUERY_H
#define BOOK_QUERY_H

#include <QDialog>
#include <QSqlQuery>
#include <QVector>
#include <QSqlDatabase>
#include <QObject>
#include <QMessageBox>
#include<qtableview.h>
#include <QtSql>

namespace Ui {
class book_query;
}

class book_query : public QDialog
{
    Q_OBJECT

public:
    explicit book_query(QWidget *parent = 0);
    ~book_query();

private slots:
    void on_pushButton_clicked();

private:
    Ui::book_query *ui;
};

#endif // BOOK_QUERY_H

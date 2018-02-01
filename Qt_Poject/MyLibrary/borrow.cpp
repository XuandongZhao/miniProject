#include "borrow.h"
#include "ui_borrow.h"
#include "Link.h"
#include "qtimer.h"
extern QString admin;

borrow::borrow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::borrow)
{
    ui->setupUi(this);
}

borrow::~borrow()
{
    delete ui;
}

void borrow::on_query_clicked()
{
    QString username;
    QSqlDatabase db;
    if(!createConnection(db))
    {
        qDebug()<<"register database not connect";
    }
    QSqlQuery query1,query2;
    query1.prepare("select * from users where username=?");
    query1.addBindValue(ui->username-text());
    query1.exec();
    if
}

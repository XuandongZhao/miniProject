#include "borrow_dialog.h"
#include "ui_borrow_dialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QFile>
#include <QString>
#include <QFileDialog>
#include <qtableview.h>
#include <QHBoxLayout>
#include <QTime>
#include "logindialog.h"
#include <QDebug>
QString ad_name;
borrow_dialog::borrow_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::borrow_dialog)
{
    ui->setupUi(this);
}

borrow_dialog::~borrow_dialog()
{
    delete ui;
}

void borrow_dialog::on_pushButton_clicked()
{
    if(ui->card_in->text().isEmpty()){
        QMessageBox::critical(NULL, "Error", "您的信息填写不完整",
                              QMessageBox::Yes);
        return;
    }
    QSqlQuery query,query1;
    query.exec(QObject::tr("select * from card where cno = N'%1'").arg(ui->card_in->text()));
    if(!query.next()){
        QMessageBox::critical(NULL, "Error", "不存在此借书证号",
                              QMessageBox::Yes);
        return;
    }
    QSqlQueryModel *model = new QSqlQueryModel;
    QDialog *mainDialog = new QDialog;
    QTableView *tableView = new QTableView;
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(tableView);
    mainDialog->setLayout(layout);
    model->setQuery(QObject::tr("select * from borrow, book where cno = N'%1' and borrow.bno = book.bno").arg(ui->card_in->text()));
    tableView->setModel(model);

    mainDialog->adjustSize();
    mainDialog->show();
}


void borrow_dialog::on_borrow_button_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    if(ui->card_in->text().isEmpty()||ui->book_in->text().isEmpty()){
        QMessageBox::critical(NULL, "Error", "您的信息填写不完整",
                              QMessageBox::Yes);
        return;
    }
    QSqlQuery query,query1,query2,query3,query4;
    query4.exec(QObject::tr("select * from card where cno = N'%1'").arg(ui->card_in->text()));
    if(!query4.next()){
        QMessageBox::critical(NULL, "Error", "不存在此借书证号",
                              QMessageBox::Yes);
        return;
    }
    query.exec(QObject::tr("select num_now from book where bno = N'%1'").arg(ui->book_in->text()));
    if(query.next()){
        int num_ = query.value(0).toInt();
        if(num_ ==0){
                           QMessageBox::critical(NULL,"error","本书籍暂无库存！");
                           QDialog *mainDialog = new QDialog;
                           QTableView *tableView = new QTableView;
                           QHBoxLayout *layout = new QHBoxLayout;
                           layout->addWidget(tableView);
                           mainDialog->setLayout(layout);
                           model->setQuery(QObject::tr("select min(return_time) from borrow where bno = N'%1'").arg(ui->book_in->text()));
                           tableView->setModel(model);

                           mainDialog->adjustSize();
                           mainDialog->show();
                    }
        else{
            query1.exec(QObject::tr("update book set num_now = num_now - 1 where bno = N'%1'").arg(ui->book_in->text()));
            QDateTime time = QDateTime::currentDateTime();
            QString str = time.toString("yyyy-MM-dd hh:mm:ss");
            QString returnDaystr=time.addDays(30).toString("yyyy-MM-dd hh:mm:ss");
            /*qDebug() <<"bno:::" <<ui->book_in->text();
            qDebug() <<"cno:::" <<ui->card_in->text();
            qDebug() <<"借书时间:::" <<str;
            qDebug() <<"还书时间:::" <<returnDaystr;*/
            query2.exec(QObject::tr
                        ("insert into borrow values(N'%1',N'%2',N'%3',N'%4',N'%5')")
                        .arg(ui->card_in->text())
                        .arg(ui->book_in->text())
                        .arg(str)
                        .arg(returnDaystr)
                        .arg(ad_name));
            QMessageBox::about(NULL,"Ok","借书成功！");
        }
    }
}

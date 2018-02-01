#include "return_dialog.h"
#include "ui_return_dialog.h"
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
return_dialog::return_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::return_dialog)
{
    ui->setupUi(this);
}

return_dialog::~return_dialog()
{
    delete ui;
}

void return_dialog::on_pushButton_clicked()
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

void return_dialog::on_return_button_clicked()
{
    QSqlQueryModel *model = new QSqlQueryModel;
    if(ui->card_in->text().isEmpty()||ui->book_in->text().isEmpty()){
        QMessageBox::critical(NULL, "Error", "您的信息填写不完整！",
                              QMessageBox::Yes);
        return;
    }
    QSqlQuery query,query1,query2,query3,query4;
    query4.exec(QObject::tr("select * from card where cno = N'%1'").arg(ui->card_in->text()));
    if(!query4.next()){
        QMessageBox::critical(NULL, "Error", "不存在此借书证号！",
                              QMessageBox::Yes);
        return;
    }
    query.exec(QObject::tr("select bno from borrow where cno = N'%1' and bno = N'%2'").arg(ui->card_in->text()).arg(ui->book_in->text()));
    if(!query.next()){
        QMessageBox::critical(NULL, "Error", "不存在此借书记录！",
                              QMessageBox::Yes);
        return;
    }
    else{
        query1.exec(QObject::tr("update book set num_now = num_now + 1 where bno = N'%1'").arg(ui->book_in->text()));
        query1.exec(QObject::tr
                    ("delete from borrow where return_time = (select min(return_time) from borrow where cno = N'%1' and bno = N'%2') and cno = N'%1' and bno = N'%2'")
                    .arg(ui->card_in->text())
                    .arg(ui->book_in->text()));
        QMessageBox::about(NULL,"Ok","还书成功！");
    }
}

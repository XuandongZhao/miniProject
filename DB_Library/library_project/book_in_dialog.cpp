#include "book_in_dialog.h"
#include "ui_book_in_dialog.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>
#include <QSqlQueryModel>
#include <QMessageBox>
#include<QFile>
#include<QString>
#include<QFileDialog>
book_in_dialog::book_in_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::book_in_dialog)
{
    ui->setupUi(this);
}

book_in_dialog::~book_in_dialog()
{
    delete ui;
}

void book_in_dialog::on_onebook_in_clicked()
{
    QSqlQuery query, query1, query2, query3;
    //检查信息
    if(ui->bno->text().isEmpty()||ui->author->text().isEmpty()||
                ui->book_name->text().isEmpty()||ui->book_publish->text().isEmpty()||
                ui->book_type->text().isEmpty()||ui->price->text().isEmpty()||ui->year->text().isEmpty() ||ui->num->text().isEmpty()){
            QMessageBox::critical(NULL, "Error", "您的信息填写不完整",
                                  QMessageBox::Yes);
            return;
    }
    //类型转换
    int num_ = ui->num->text().toInt();
    int year_ = ui->year->text().toInt();
    double price_ = ui->price->text().toDouble();
    //如果已存在此类书籍，则书籍数增加
     query.exec(QObject::tr("select book_name from book where bno = N'%1'and book_name = N'%2' and book_type = N'%3' and book_publish = N'%4' and years = %5 and author = N'%6' and price = %7")
                    .arg(ui->bno->text())
                    .arg(ui->book_name->text())
                    .arg(ui->book_type->text())
                    .arg(ui->book_publish->text())
                    .arg(year_)
                    .arg(ui->author->text())
                    .arg(price_));
     if(query.next()){
         query1.exec(QObject::tr
                     ("update book set num = num + %1 , num_now = num_now + %1 where bno = N'%2'and book_name = N'%3' and book_type = N'%4' and book_publish = N'%5' and years = %6 and author = N'%7' and price = %8")
                     .arg(num_)
                     .arg(ui->bno->text())
                     .arg(ui->book_name->text())
                     .arg(ui->book_type->text())
                     .arg(ui->book_publish->text())
                     .arg(year_)
                     .arg(ui->author->text())
                     .arg(price_));
         QMessageBox::about(NULL,"Ok","入库成功");
     }
     else{
         //如果有书号重复但其他信息不同
         query3.exec(QObject::tr
                     ("select * from book where bno = N'%1'").arg(ui->bno->text()));
         if(query3.next()){
             QMessageBox::critical(NULL, "Error", "书号不可以重复！",
                                   QMessageBox::Yes);
             return;
         }
         //书号没有不同添加新书
         query2.exec(QObject::tr
                     ("insert into book values(N'%1',N'%2',N'%3',N'%4',%5,N'%6',%7,%8,%8)")
                     .arg(ui->bno->text())
                     .arg(ui->book_type->text())
                     .arg(ui->book_name->text())
                     .arg(ui->book_publish->text())
                     .arg(year_)
                     .arg(ui->author->text())
                     .arg(price_)
                     .arg(num_));
          QMessageBox::about(NULL,"Ok","入库成功");
     }
    return;
}
void book_in_dialog::readfile(QFile &file)
{
    //打开文件批量填入书，必须按照特定顺序
    QSqlQueryModel *model = new QSqlQueryModel;
    file.open(QIODevice::ReadOnly);
    auto buf = file.readAll();
    auto content = QString::fromLocal8Bit(buf);
    auto lines = content.split("\r\n");
    for (auto &s : lines){
        QStringList list1 = s.split(",");
        int year_ = list1[4].toInt();
        double price_ = list1[6].toDouble();
        int num_ = list1[7].toInt();
        model->setQuery(QObject::tr
                        ("insert into book values(N'%1',N'%2',N'%3',N'%4',%5,N'%6',%7,%8,%8)")
                        .arg(list1[0])
                        .arg(list1[1])
                        .arg(list1[2])
                        .arg(list1[3])
                        .arg(year_)
                        .arg(list1[5])
                        .arg(price_)
                        .arg(num_));
        QMessageBox::about(NULL,"Ok","入库成功");
    }
}
void book_in_dialog::on_nbook_in_clicked()
{
    QFileDialog dlg(this);
    dlg.exec();
    auto file = dlg.selectedFiles();
    if(!file.isEmpty()){
        QFile f;
        f.setFileName(file.at(0));
        readfile(f);
     }
}

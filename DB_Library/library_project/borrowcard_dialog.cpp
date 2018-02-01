#include "borrowcard_dialog.h"
#include "ui_borrowcard_dialog.h"
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
borrowcard_dialog::borrowcard_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::borrowcard_dialog)
{
    ui->setupUi(this);
}

borrowcard_dialog::~borrowcard_dialog()
{
    delete ui;
}

void borrowcard_dialog::on_input_button_clicked()
{
    if(ui->department->text().isEmpty()||ui->nameinput->text().isEmpty()||ui->cardnum->text().isEmpty()){
        QMessageBox::critical(NULL, "Error", "您的信息填写不完整",
                              QMessageBox::Yes);
        return;
    }
    QSqlQuery query,query1,query2;
    query.exec(QObject::tr
               ("select * from card where cno = N'%1' and name = N'%2' and department = N'%3' and type = N'%4'")
               .arg(ui->cardnum->text())
               .arg(ui->nameinput->text())
               .arg(ui->department->text())
               .arg(ui->comboBox->currentText()));
    if(query.next()){
        QMessageBox::critical(NULL, "Error", "此借书证已经存在！",
                              QMessageBox::Yes);
        return;
    }
    else{
        query2.exec(QObject::tr
                    ("select * from card where cno = N'%1'").arg(ui->cardnum->text()));

        if(query2.next()){
            QMessageBox::critical(NULL, "Error", "此借书证号已经存在！",
                                  QMessageBox::Yes);
            return;
        }
        query1.exec(QObject::tr
                    ("insert into card values(N'%1',N'%2',N'%3',N'%4')")
                    .arg(ui->cardnum->text())
                    .arg(ui->nameinput->text())
                    .arg(ui->department->text())
                    .arg(ui->comboBox->currentText()));
        QMessageBox::about(NULL,"Ok","借书卡申请成功！");
    }
}

void borrowcard_dialog::on_delete_button_clicked()
{
    if(ui->department->text().isEmpty()||ui->nameinput->text().isEmpty()||ui->cardnum->text().isEmpty()){
        QMessageBox::critical(NULL, "Error", "您的信息填写不完整",
                              QMessageBox::Yes);
        return;
    }
    QSqlQuery query,query1,query2;
    query.exec(QObject::tr
               ("select * from card where cno = N'%1' and name = N'%2' and department = N'%3' and type = N'%4'")
               .arg(ui->cardnum->text())
               .arg(ui->nameinput->text())
               .arg(ui->department->text())
               .arg(ui->comboBox->currentText()));
    if(!query.next()){
        QMessageBox::critical(NULL, "Error", "此借书证不存在！",
                              QMessageBox::Yes);
        return;
    }
    else{
        query2.exec(QObject::tr("select * from borrow where cno = N'%1'").arg(ui->cardnum->text()));
        if(query2.next()){
            QMessageBox::critical(NULL, "Error", "该证有借书记录，需先还书才能删除！",
                                  QMessageBox::Yes);
            return;
        }else{
        query1.exec(QObject::tr
                    ("delete from card where cno = N'%1' and name = N'%2' and department = N'%3' and type = N'%4'")
                    .arg(ui->cardnum->text())
                    .arg(ui->nameinput->text())
                    .arg(ui->department->text())
                    .arg(ui->comboBox->currentText()));
        QMessageBox::about(NULL,"Ok","借书卡删除成功！");
      }
        }
}

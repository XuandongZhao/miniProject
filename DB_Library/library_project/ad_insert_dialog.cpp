#include "ad_insert_dialog.h"
#include "ui_ad_insert_dialog.h"
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
ad_insert_dialog::ad_insert_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ad_insert_dialog)
{
    ui->setupUi(this);
    ui->password_input->setEchoMode(QLineEdit::Password);
    ui->password_check->setEchoMode(QLineEdit::Password);
}

ad_insert_dialog::~ad_insert_dialog()
{
    delete ui;
}

void ad_insert_dialog::on_add_button_clicked()//添加管理员账号
{
    //检查信息是否完整
    if(ui->id_input->text().isEmpty()||ui->name_input->text().isEmpty()||ui->address_input->text().isEmpty()||ui->password_check->text().isEmpty()||
            ui->password_input->text().isEmpty()){
        QMessageBox::critical(NULL, "Error", "您的信息填写不完整",
                              QMessageBox::Yes);
        return;
    }
    //检查密码相同
    if(ui->password_check->text()!=ui->password_input->text()){
        QMessageBox::critical(NULL, "Error", "两次密码填写不同！",
                              QMessageBox::Yes);
        return;
    }
    //对已有管理员进行查询，如已存在则无法插入
    QSqlQuery query,query1;
    query.exec(QObject::tr
               ("select * from Administrator where administrator_ID = N'%1' and administrator_password = N'%2' and ad_name = N'%3' and address = N'%4'")
               .arg(ui->id_input->text())
               .arg(ui->password_input->text())
               .arg(ui->name_input->text())
               .arg(ui->address_input->text()));
    if(query.next()){
        QMessageBox::critical(NULL, "Error", "此管理员已经存在！",
                              QMessageBox::Yes);
        return;
    }
    else{
        //添加管理员
        query1.exec(QObject::tr
                    ("insert into Administrator values(N'%1',N'%2',N'%3',N'%4')")
                    .arg(ui->id_input->text())
                    .arg(ui->password_input->text())
                    .arg(ui->name_input->text())
                    .arg(ui->address_input->text()));
        QMessageBox::about(NULL,"Ok","管理员添加成功！");
    }
}

void ad_insert_dialog::on_delete_button_clicked()
{
    //检查信息是否完整
    if(ui->id_input->text().isEmpty()||ui->name_input->text().isEmpty()||ui->address_input->text().isEmpty()||ui->password_check->text().isEmpty()||
            ui->password_input->text().isEmpty()){
        QMessageBox::critical(NULL, "Error", "您的信息填写不完整",
                              QMessageBox::Yes);
        return;
    }
    if(ui->password_check->text()!=ui->password_input->text()){
        QMessageBox::critical(NULL, "Error", "两次密码填写不同！",
                              QMessageBox::Yes);
        return;
    }

    //查询管理员存在情况
    QSqlQuery query,query1;
    query.exec(QObject::tr
               ("select * from Administrator where administrator_ID = N'%1' and administrator_password = N'%2' and ad_name = N'%3' and address = N'%4'")
               .arg(ui->id_input->text())
               .arg(ui->password_input->text())
               .arg(ui->name_input->text())
               .arg(ui->address_input->text()));
    if(!query.next()){
        QMessageBox::critical(NULL, "Error", "此管理员不存在！",
                              QMessageBox::Yes);
        return;
    }
    else{
        //删除管理员
        query1.exec(QObject::tr
                    ("delete from Administrator where administrator_ID = N'%1' and administrator_password = N'%2' and ad_name = N'%3' and address = N'%4'")
                    .arg(ui->id_input->text())
                    .arg(ui->password_input->text())
                    .arg(ui->name_input->text())
                    .arg(ui->address_input->text()));
        QMessageBox::about(NULL,"Ok","管理员删除成功！");
    }
}

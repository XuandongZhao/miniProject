#include "logindialog.h"
#include "ui_logindialog.h"
#include <QCompleter>
#include <QDebug>
#include <QMessageBox>
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QSqlQuery>
extern QString ad_name;
logindialog::logindialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logindialog)
{
    ui->setupUi(this);

    setWindowTitle(tr("登陆"));//窗口标题
    QStringList strings;
    strings << "Tom" << "Jack" << "Mike";
    completer = new QCompleter(strings, this);
    ui->name_input->clear();
    ui->name_input->addItems(strings);
    ui->name_input->setEditable(true);
    ui->name_input->setCompleter(completer);
    qDebug()<<__FUNCTION__<<"is running !";

    ui->password_input->setEchoMode(QLineEdit::Password);//密码方式显示文本
    QDialog::setModal( true );//设置模态，让该窗口一直在最前端
    setAttribute(Qt::WA_DeleteOnClose,true);//关闭后释放内存
    ui->password_input->setFocus();//设置焦点
}

logindialog::~logindialog()
{
    delete ui;
}

void logindialog::on_login_button_clicked()
{
    qDebug()<<ui->name_input->currentText();
    QSqlTableModel model;
    QSqlQuery query;
    model.setTable("Administrator");
    model.select();
    int userCnt = 0;
    for(int i=0;i<model.rowCount();++i)//遍历数据库中的管理员信息，并进行核对
    {
        QSqlRecord record = model.record(i);
        QString name = record.value("administrator_ID").toString();
        QString passWord = record.value("administrator_password").toString();
        //qDebug()<<name<<passWord<<__FUNCTION__;
        if(ui->name_input->currentText() == name){
            //qDebug()<<"用户名正确!";
            if(ui->password_input->text() == passWord){
                QString str = ui->name_input->currentText();
                //qDebug()<<str;
                ad_name = str;
                emit passWordIsRight();//密码正确传信号给Mainwindow,从而显示参数设置界面
                this->close();

            }
            else{
                QMessageBox msgBox(this);
                msgBox.setText("The password is wrong.");
                msgBox.exec();
            }
            userCnt++;
        }
    }
    if(!userCnt)
    {
        QMessageBox msgBox(this);
        msgBox.setText("该用户不存在！");
        msgBox.exec();
    }

}

void logindialog::on_exit_button_clicked()
{
    exit(-1);
}

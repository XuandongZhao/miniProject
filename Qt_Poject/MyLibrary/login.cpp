#include "login.h"
#include "ui_login.h"
//#include "regeister_"
#include "Link.h"
#include <QPainter>
QString admin;

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    setWindowTitle(tr("LOG IN"));
    ui->loginpassword->setEchoMode(QLineEdit::Password);
    connect(ui->loginpassword,SIGNAL(returnPressed()),this,SLOT(on_loginb_clicked()));
}

Login::~Login()
{
    delete ui;
}

void Login::on_exitb_clicked()
{
    QDialog::reject();
}

void Login::on_signb_clicked()
{

}

void Login::on_loginb_clicked()
{
    qDebug()<<ui->loginID->currentText();
    if(ui->loginID->text().isEmpty())
    {
        QMessageBox::information(this,tr("login failed"),tr("Please enter your ID!"),QMessageBox::Ok);
        ui->loginID->setFocus();
    }
    else if(ui->loginpassword->text().isEmpty())
    {
        QMessageBox::information(this,tr("login failed"),tr("Please enter your password"),QMessageBox::Ok);
        ui->loginpassword->setFocus();
    }
    else
    {
        QSqlDatabase db;
        if(!createConnection(db))
        {
            qDebug()<<"Login database not connect";
        }
        QSqlQuery query;
        query.prepare("select * from users where username =?");
        query.addBindValue(ui->loginID->text());
        query.exec();
        if(query.next())
        {
            if(query.value(1).toString() == ui->loginID->text())
            {
                admin = ui->loginID->text();
                qDebug()<<admin<<endl;
                QDialog::accept();
            }
            else
            {
                QMessageBox::warning(this,tr("wrong password or id"),tr("Please reenter!"),QMessageBox::Ok);
                ui->loginID->clear();
                ui->loginpassword->clear();
                ui->loginID->setFocus();
            }
        }
        else
            QMessageBox::information(this,tr("reference"),tr("there is no such id!"),QMessageBox::Ok);
        db.close();
    }
}

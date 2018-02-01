#include "logindialog.h"
#include "ui_logindialog.h"
#include "register_pro.h"
#include "connection.h"
#include <QPainter>
QString admin;

LoginDialog::~LoginDialog()
{
	delete ui;
}

LoginDialog::LoginDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::LoginDialog)
{
	ui->setupUi(this);

	setWindowTitle(tr("LOG IN"));
	ui->logPwdLE->setEchoMode(QLineEdit::Password);
	connect(ui->logPwdLE, SIGNAL(returnPressed()), this, SLOT(on_loginBtn_clicked()));

}
//登录按钮
void LoginDialog::on_loginBtn_clicked()
{
	if (ui->logIdLE->text().isEmpty())
	{
		QMessageBox::information(this, tr("fail log in"), tr("please enter ID!"), QMessageBox::Ok);
		ui->logIdLE->setFocus();
	}
	else if (ui->logPwdLE->text().isEmpty())
	{
		QMessageBox::information(this, tr("fail log in"), tr("please enter password"), QMessageBox::Ok);
		ui->logPwdLE->setFocus();
	}
	else
	{
		QSqlDatabase db;
		if (!createConnection(db))
		{
			qDebug() << "logindialog database not connect";
		}
		QSqlQuery query(db);
		query.prepare("select * from administrator where ano=?");
		query.addBindValue(ui->logIdLE->text());
		query.exec();
		if (query.next())
		{
			if (query.value(1).toString() == ui->logPwdLE->text())
			{
				admin = ui->logIdLE->text();
				qDebug() << admin << endl;
				QDialog::accept();
			}
			else
			{
				QMessageBox::warning(this, tr("wrong password or id"),
					tr("please reenter!!!"), QMessageBox::Ok);
				ui->logIdLE->clear();
				ui->logPwdLE->clear();
				ui->logIdLE->setFocus();
			}
		}
		else
			QMessageBox::information(this, tr("reference"), tr("there is no such id!"), QMessageBox::Ok);
		db.close();
	}
}
//退出按钮
void LoginDialog::on_exitBtn_clicked()
{
	QDialog::reject();
}


//注册按钮
void LoginDialog::on_regBtn_clicked()
{
	Register_pro regDlg;
	regDlg.exec();
}





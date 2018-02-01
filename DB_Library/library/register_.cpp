#include "register_.h"
#include "ui_register.h"

#include "connection.h"
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDebug>

register::register(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::register)
{
	ui->setupUi(this);
}

register::~register()
{
	delete ui;
}

//关闭窗口
void Register::on_exitBtn_clicked()
{
	this->close();
}
//清空
void Register::on_clearBtn_clicked()
{
	ui->logIdLE->clear();
	ui->logPwdLE->clear();
	ui->logPwdSure->clear();
	ui->emailLE->clear();
	ui->qqLE->clear();
}
//提交注册
void Register::on_sumBtn_clicked()
{
	QString logid, pwd, email, qq;
	//int pwd;//64

	QSqlDatabase db;
	if (!createConnection(db))
	{

		qDebug() << "register database not connect";
	}
	QSqlQuery query, query1, query2;
	query.exec("create table if not exists Tuser(id varchar(20) primary key,pwd varchar(15),email varchar(20),qq varchar(20))");

	query.prepare("select * from Tuser where id=?");
	query.addBindValue(ui->logIdLE->text());
	query.exec();
	if (query.size()>0)
	{
		QMessageBox::warning(this, tr("failed"), tr("The id has all ready exist,please change one"), QMessageBox::Close);
		ui->logIdLE->clear();

	}
	else if (ui->logIdLE->text() == NULL)
	{
		QMessageBox::warning(this, tr("failed"), tr("User id can not be NULL"), QMessageBox::Close);

	}
	else if (ui->logPwdLE->text() != ui->logPwdSure->text())
	{
		QMessageBox::warning(this, tr("failed"), tr("The password is not same"), QMessageBox::Close);
		ui->logPwdLE->clear();
		ui->logPwdSure->clear();

	}
	else {
		logid = ui->logIdLE->text();
		pwd = ui->logPwdLE->text();
		email = ui->emailLE->text();
		qq = ui->qqLE->text();
		query1.prepare("insert into Tuser(id,pwd,email,qq)" "values(:id,:pwd,:email,:qq)");
		query1.bindValue(":id", logid);
		query1.bindValue(":pwd", pwd);
		//query1.bindValue(":level",1);
		query1.bindValue(":email", email);
		query1.bindValue(":qq", qq);
		if (!query1.exec())
		{

			QMessageBox::warning(this, tr("failed"), tr("注册失败！"), QMessageBox::Close);
			qDebug() << "this 5 register error:" << query1.lastError();
		}
		else
		{
			bool flag = query2.exec("create table " + logid + "(bookId varchar(10) primary key,bookName varchar(20),authorName varchar(20),"
				"lendDate varchar(20),backDate varchar(20))");
			if (!flag)
				qDebug() << query2.lastError();
			else
				qDebug() << "create table " << logid;
			QMessageBox::information(this, tr("success"), tr("注册成功！"), QMessageBox::Ok);
			ui->logIdLE->clear();
			ui->logPwdLE->clear();
			ui->logPwdSure->clear();
			ui->emailLE->clear();
			ui->qqLE->clear();
			this->close();
		}
	}
	db.close();
}

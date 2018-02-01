#include "register_pro.h"
#include "ui_register_pro.h"
#include "connection.h"


Register_pro::Register_pro(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Register_pro)
{
	ui->setupUi(this);

	setWindowTitle(tr("Register"));
}

Register_pro::~Register_pro()
{
	delete ui;
}

//关闭窗口
void Register_pro::on_exitBtnr_clicked()
{
	this->close();
}
//清空
void Register_pro::on_clearBtn_clicked()
{
	ui->logIdLE_R->clear();
	ui->logPwdLE_R->clear();
	ui->logPwdSure->clear();
	ui->nameLE->clear();
	ui->telLE->clear();
}
//提交注册
void Register_pro::on_sumBtn_clicked()
{
	QString logid, pwd, name, telephone;

	QSqlDatabase db;
	if (!createConnection(db))
	{

		qDebug() << "register database not connect";
	}
	QSqlQuery query, query1;


	query.prepare("select * from administrator where ano=?");
	query.addBindValue(ui->logIdLE_R->text());
	query.exec();
	if (query.size()>0)
	{
		QMessageBox::warning(this, tr("failed"), tr("The id has already exist,please change one"), QMessageBox::Close);
		ui->logIdLE_R->clear();

	}
	else if (ui->logIdLE_R->text() == NULL)
	{
		QMessageBox::warning(this, tr("failed"), tr("User id can not be NULL"), QMessageBox::Close);

	}
	else if (ui->logPwdLE_R->text() != ui->logPwdSure->text())
	{
		QMessageBox::warning(this, tr("failed"), tr("The password is not same"), QMessageBox::Close);
		ui->logPwdLE_R->clear();
		ui->logPwdSure->clear();

	}
	else {
		logid = ui->logIdLE_R->text();
		pwd = ui->logPwdLE_R->text();
		name = ui->nameLE->text();
		telephone = ui->telLE->text();
		query1.prepare("insert into administrator values(:id,:pwd,:name,:telephone)");
		query1.bindValue(":id", logid);
		query1.bindValue(":pwd", pwd);
		query1.bindValue(":name", name);
		query1.bindValue(":telephone", telephone);
		if (!query1.exec())
		{

			QMessageBox::warning(this, tr("failed"), tr("sign in fail!"), QMessageBox::Close);
			qDebug() << "this 5 register error:" << query1.lastError();
		}
		else
		{

			QMessageBox::information(this, tr("success"), tr("sign in succeed!"), QMessageBox::Ok);
			ui->logIdLE_R->clear();
			ui->logPwdLE_R->clear();
			ui->logPwdSure->clear();
			ui->nameLE->clear();
			ui->telLE->clear();
			this->close();
		}
	}
	db.close();
}

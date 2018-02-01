#include "managecard.h"
#include "ui_managecard.h"
#include "connection.h"

manageCard::manageCard(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::manageCard)
{
	ui->setupUi(this);
	setWindowTitle(tr("Manage Card"));
}

manageCard::~manageCard()
{
	delete ui;
}

void manageCard::on_clear_clicked()
{
	ui->card->clear();
	ui->name->clear();
	ui->department->clear();
	ui->type->clear();
}

void manageCard::on_exit_clicked()
{
	this->close();
}

void manageCard::on_add_clicked()
{
	QString card, name, department, type;

	QSqlDatabase db;
	if (!createConnection(db))
	{
		qDebug() << "register database not connect";
	}
	QSqlQuery query, query1;
	query.prepare("select * from card where cno=? ");
	query.addBindValue(ui->card->text());
	query.exec();
	if (query.size()>0)
	{
		QMessageBox::warning(this, tr("failed"), tr("There is already such card,please change one"), QMessageBox::Close);
		ui->card->clear();
	}
	else if (ui->card->text() == NULL || ui->name->text() == NULL || ui->department->text() == NULL || ui->type->text() == NULL)
	{
		QMessageBox::warning(this, tr("failed"), tr("The information is not defined all"), QMessageBox::Close);
	}
	else {
		card = ui->card->text();
		name = ui->name->text();
		department = ui->department->text();
		type = ui->type->text();
		query1.prepare("insert into card(cno,name,department,type)" "values(:cno,:name,:department,:type)");
		query1.bindValue(":cno", card);
		query1.bindValue(":name", name);
		query1.bindValue(":department", department);
		query1.bindValue(":type", type);
		if (!query1.exec())
		{
			QMessageBox::warning(this, tr("failed"), tr("fail to add"), QMessageBox::Close);
		}
		else
		{
			QMessageBox::information(this, tr("success"), tr("succeed to add"), QMessageBox::Ok);
			ui->card->clear();
			ui->name->clear();
			ui->department->clear();
			ui->type->clear();
			this->close();
		}

	}
	db.close();

}




void manageCard::on_delete_2_clicked()
{
	QSqlDatabase db;
	if (!createConnection(db))
	{
		qDebug() << "register database not connect";
	}
    QSqlQuery query, query1, query2;
	query.prepare("select * from card where cno=? ");
	query.addBindValue(ui->card->text());
	query.exec();
	if (query.size() == 0)
	{
		QMessageBox::warning(this, tr("failed"), tr("There is no such card,please change one"), QMessageBox::Close);
		ui->card->clear();
	}
	else if (ui->card->text() == NULL)
	{
		QMessageBox::warning(this, tr("failed"), tr("The information is not defined all"), QMessageBox::Close);
	}
    else
    {
        query2.prepare("select * from borrow where cno =?");
        query2.addBindValue(ui->card->text());
        query2.exec();
        if(query2.size() == 0)
        {
            query1.prepare("delete from card where cno =? ");
            query1.addBindValue(ui->card->text());

            if (!query1.exec())
            {
                QMessageBox::warning(this, tr("failed"), tr("fail to delete"), QMessageBox::Close);
            }
            else
            {
                QMessageBox::information(this, tr("success"), tr("succeed to delete"), QMessageBox::Ok);
                ui->card->clear();
                ui->name->clear();
                ui->department->clear();
                ui->type->clear();
                this->close();
            }
        }
        else
        {
            QMessageBox::warning(this, tr("failed"), tr("The card should return the book before deleted"), QMessageBox::Close);
        }
	}
	db.close();

}


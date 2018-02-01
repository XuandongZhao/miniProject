#include "returnbooks.h"
#include "ui_returnbooks.h"
#include "connection.h"

returnbooks::returnbooks(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::returnbooks)
{
	ui->setupUi(this);
}

returnbooks::~returnbooks()
{
	delete ui;
}

void returnbooks::on_exit_clicked()
{
	this->close();
}


void returnbooks::on_clear_clicked()
{
	{
		ui->bookid->clear();
		ui->card->clear();
		ui->tableWidget->clear();
		ui->tableWidget->setColumnCount(0);
		ui->tableWidget->setRowCount(0);
	}
}

void returnbooks::on_query_clicked()
{
	QString cno;

	QSqlDatabase db;
	if (!createConnection(db))
	{
		qDebug() << "register database not connect";
	}
	QSqlQuery query, query1;
	query.prepare("select * from card where cno=? ");
	query.addBindValue(ui->card->text());
	query.exec();
	if (query.size() == 0)
	{
		QMessageBox::warning(this, tr("failed"), tr("This card does not exist, please change"), QMessageBox::Close);
		ui->card->clear();
	}
	else {
		cno = ui->card->text();
		query1.prepare("select * from borrow join book using (bno) where cno=? ");
		query1.addBindValue(ui->card->text());
		query1.exec();
		int i = 0;
		ui->tableWidget->setRowCount(query1.size());
		ui->tableWidget->setColumnCount(13);
		QStringList header;
		header << "bno" << "cno" << "borrow_date" << "return_date" << "ano" << "category";
		header << "title" << "press" << "year" << "author" << "price" << "total" << "stock";
		ui->tableWidget->setHorizontalHeaderLabels(header);

		while (query1.next())
		{
			ui->tableWidget->setItem(i, 0, new QTableWidgetItem(query1.value(0).toString()));
			ui->tableWidget->setItem(i, 1, new QTableWidgetItem(query1.value(1).toString()));
			ui->tableWidget->setItem(i, 2, new QTableWidgetItem(query1.value(2).toString()));
			ui->tableWidget->setItem(i, 3, new QTableWidgetItem(query1.value(3).toString()));
			ui->tableWidget->setItem(i, 4, new QTableWidgetItem(query1.value(4).toString()));
			ui->tableWidget->setItem(i, 5, new QTableWidgetItem(query1.value(5).toString()));
			ui->tableWidget->setItem(i, 6, new QTableWidgetItem(query1.value(6).toString()));
			ui->tableWidget->setItem(i, 7, new QTableWidgetItem(query1.value(7).toString()));
			ui->tableWidget->setItem(i, 8, new QTableWidgetItem(query1.value(8).toString()));
			ui->tableWidget->setItem(i, 9, new QTableWidgetItem(query1.value(9).toString()));
			ui->tableWidget->setItem(i, 10, new QTableWidgetItem(query1.value(10).toString()));
			ui->tableWidget->setItem(i, 11, new QTableWidgetItem(query1.value(11).toString()));
			ui->tableWidget->setItem(i, 12, new QTableWidgetItem(query1.value(12).toString()));
			i++;
		}
	}
	db.close();
}


void returnbooks::on_return_2_clicked()
{
	QSqlDatabase db;
	if (!createConnection(db))
	{
		qDebug() << "register database not connect";
	}
	QSqlQuery query, query1;
	query.prepare("select * from borrow where bno=:bno and cno=:cno ");
	query.bindValue(":bno", ui->bookid->text());
	query.bindValue(":cno", ui->card->text());
	query.exec();

	if (query.size() == 0)
	{
		QMessageBox::warning(this, tr("failed"), tr("This book has not been borrowed!"), QMessageBox::Close);
		ui->bookid->clear();
	}
	else if (query.next())  // 下一行有东西
	{
		QSqlQuery query3;
		query3.prepare("delete from borrow where bno=:bno and cno=:cno and borrow_date=(select min(borrow_date) from (select * from borrow where bno=:bno and cno=:cno) as A)");
		query3.bindValue(":bno", ui->bookid->text());
		query3.bindValue(":cno", ui->card->text());
		bool flag = query3.exec();
		if (flag) {
			QMessageBox::information(this, tr("Return success"), tr("Return success"), QMessageBox::Ok);
			query1.prepare("update book set stock = stock+1 where bno =?");
			query1.addBindValue(ui->bookid->text());
			query1.exec();
			ui->bookid->clear();
			//ui->card->clear();
			ui->tableWidget->clear();
		}
		else QMessageBox::warning(this, tr("failed"), tr("Return failed!"), QMessageBox::Close);

	}
	db.close();

}


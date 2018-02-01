#include "borrowbooks.h"
#include "ui_borrowbooks.h"
#include "qtimer.h"
#include "connection.h"

extern QString admin;

borrowBooks::borrowBooks(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::borrowBooks)
{
	ui->setupUi(this);
}

borrowBooks::~borrowBooks()
{
	delete ui;
}

void borrowBooks::on_exit_clicked()
{
	this->close();
}

void borrowBooks::on_clear_clicked()
{
	{
		ui->bookid->clear();
		ui->card->clear();
		ui->tableWidget->clear();
		ui->tableWidget->setColumnCount(0);
		ui->tableWidget->setRowCount(0);
	}
}

void borrowBooks::on_query_clicked()
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
        QMessageBox::warning(this, tr("failed"), tr("This card does not exist"), QMessageBox::Close);
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


void borrowBooks::on_borrow_clicked()
{
	QDateTime time = QDateTime::currentDateTime();
	QString str = time.toString("yyyy_MM_dd hh:mm:ss");
	QDateTime time_1 = time.addMonths(3);
	QString str_1 = time_1.toString("yyyy_MM_dd hh:mm:ss");
	QSqlDatabase db;
	if (!createConnection(db))
	{
		qDebug() << "register database not connect";
	}
	QSqlQuery query, query1, query2;
	query.prepare("select stock from book where bno=? ");
	query.addBindValue(ui->bookid->text());
	query.exec();

	if (query.size() == 0)
	{
		QMessageBox::warning(this, tr("failed"), tr("This book has not been stored!"), QMessageBox::Close);
		ui->bookid->clear();
	}
	else if (query.next())  // 下一行有东西
	{
		if (query.value(0) == 0)  // 没有存书
		{
			QSqlQuery query3;
			query3.prepare("select min(return_date) from borrow where bno=? ");
			query3.addBindValue(ui->bookid->text());
			query3.exec();
			query3.next();
			QString tmpS = "This book has been borrowed! The book will be available after " + query3.value(0).toString();
			QMessageBox::warning(this, tr("failed"), tmpS, QMessageBox::Close);
			ui->bookid->clear();
		}
		else 
		{
			query1.prepare("update book set stock = stock-1 where bno =?");
			query1.addBindValue(ui->bookid->text());

			if (!query1.exec())
			{
				QMessageBox::warning(this, tr("failed"), tr("fail to borrow1"), QMessageBox::Close);
			}
			query2.prepare("insert into borrow(cno,bno,borrow_date,return_date,ano)" "values(:cno,:bno,:borrow_date,:return_date,:ano)");
			query2.bindValue(":cno", ui->card->text());
			query2.bindValue(":bno", ui->bookid->text());
			query2.bindValue(":borrow_date", str);
			query2.bindValue(":return_date", str_1);
			query2.bindValue(":ano", admin);
			qDebug() << "In borrow:" << admin << endl;
			if (!query2.exec())
			{
                QMessageBox::warning(this, tr("failed"), tr("fail to borrow2"), QMessageBox::Close);
			}
			else
			{
				QMessageBox::information(this, tr("success"), tr("succeed to borrow"), QMessageBox::Ok);
				ui->bookid->clear();
				ui->card->clear();
				ui->tableWidget->clear();
			}
		}
	}
	db.close();
}



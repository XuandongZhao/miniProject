#include "askbooks.h"
#include "ui_askbooks.h"
#include "connection.h"

askBooks::askBooks(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::askBooks)
{
	ui->setupUi(this);
}

askBooks::~askBooks()
{
	delete ui;
}

void askBooks::on_Go_clicked() {
	QString cno;

	QSqlDatabase db;
	if (!createConnection(db))
	{
		qDebug() << "register database not connect";
	}
	QSqlQuery query, query1;
	QString s_cat, s_title, s_press, s_author, s_year, t_year, s_price, t_price;
	QString query_order;
	s_cat = (ui->category->text() == NULL) ? "%" : ("%" + ui->category->text() + "%");
	s_title = (ui->title->text() == NULL) ? "%" : ("%" + ui->title->text() + "%");
	s_press = (ui->press->text() == NULL) ? "%" : ("%" + ui->press->text() + "%");
	s_author = (ui->author->text() == NULL) ? "%" : ("%" + ui->author->text() + "%");
	s_year = (ui->s_year->text() == NULL) ? "0" : ui->s_year->text();
	t_year = (ui->t_year->text() == NULL) ? "9999" : ui->t_year->text();
	s_price = (ui->s_price->text() == NULL) ? "0.00" : ui->s_price->text();
	t_price = (ui->t_price->text() == NULL) ? "9999999.99" : ui->t_price->text();
	query_order = ui->comboBox->currentText();
	QString p1 = "select * from book where category like \'" + s_cat + "\' and title like \'" + s_title
		+ "\' and press like \'" + s_press + "\' and author like \'" + s_author + "\' and year between " + s_year + " and " + t_year
		+ " and price between " + s_price + " and " + t_price + " order by " + query_order;
	qDebug() << p1;
	query.prepare(p1);
	if (!query.exec()) {
		QMessageBox::warning(this, tr("Failed"), tr("Query failed!"), QMessageBox::Close);
		return;
	}
	qDebug() << query.size() << endl;
	if (query.size() == 0)
	{
		QMessageBox::warning(this, tr("Failed"), tr("Such books doesn\'t exist!"), QMessageBox::Close);
	}
	else {
		int i = 0;
		ui->tableWidget->setRowCount(query.size());
		ui->tableWidget->setColumnCount(9);
		QStringList header;
		header << "bno" << "category" << "title" << "press" << "year" << "author" << "price" << "total" << "stock";
		ui->tableWidget->setHorizontalHeaderLabels(header);

		while (query.next())
		{
			ui->tableWidget->setItem(i, 0, new QTableWidgetItem(query.value(0).toString()));
			ui->tableWidget->setItem(i, 1, new QTableWidgetItem(query.value(1).toString()));
			ui->tableWidget->setItem(i, 2, new QTableWidgetItem(query.value(2).toString()));
			ui->tableWidget->setItem(i, 3, new QTableWidgetItem(query.value(3).toString()));
			ui->tableWidget->setItem(i, 4, new QTableWidgetItem(query.value(4).toString()));
			ui->tableWidget->setItem(i, 5, new QTableWidgetItem(query.value(5).toString()));
			ui->tableWidget->setItem(i, 6, new QTableWidgetItem(query.value(6).toString()));
			ui->tableWidget->setItem(i, 7, new QTableWidgetItem(query.value(7).toString()));
			ui->tableWidget->setItem(i, 8, new QTableWidgetItem(query.value(8).toString()));
			i++;
		}
	}
	db.close();
}

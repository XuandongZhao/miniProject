#include "insertbook.h"
#include "ui_insertbook.h"
#include "connection.h"
#include "qfiledialog.h"
#include <QSqlQueryModel>
#include <QFile>
#include <QString>
#include <QFileDialog>
#include <QSqlQuery>
#include <QObject>

insertbook::insertbook(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::insertbook)
{
	ui->setupUi(this);

	setWindowTitle(tr("Insert Books"));
}

insertbook::~insertbook()
{
	delete ui;
}

void insertbook::on_exit_clicked()
{
	this->close();
}

void insertbook::on_clear_clicked()
{
	ui->bookId->clear();
	ui->category->clear();
	ui->title->clear();
	ui->press->clear();
	ui->year->clear();
	ui->author->clear();
	ui->price->clear();
	ui->total->clear();
	ui->stock->clear();
}

void insertbook::on_insert_clicked()
{
	QString bookid, category, title, press, author;
	QString total_s, stock_s, year_s, price_s;
	int total, stock, year;
	float price;

	QSqlDatabase db;
	if (!createConnection(db))
	{
		qDebug() << "register database not connect";
	}
	QSqlQuery query, query1;
    query.prepare("select * from book where bno=:bno and category = :category and title = :title ");
    query.bindValue(":bno", ui->bookId->text());
    query.bindValue(":category", ui->category->text());
    query.bindValue(":title", title = ui->title->text());
	query.exec();
	if (query.size()>0)
	{
        QMessageBox::warning(this, tr("failed"), tr("The bookId has all ready exist"), QMessageBox::Close);
        //ui->bookId->clear();
        query1.prepare("update book set total = total + :1,stock = stock + :2 where bno = :bno");
        query1.bindValue(":1",ui->total->text());
        query1.bindValue(":2",ui->stock->text());
        query1.bindValue(":bno",ui->bookId->text());
        query1.exec();
	}
	else if (ui->bookId->text() == NULL || ui->category->text() == NULL || ui->title->text() == NULL || ui->press->text() == NULL || ui->author->text() == NULL ||
		ui->total->text() == NULL || ui->stock->text() == NULL || ui->price->text() == NULL || ui->year->text() == NULL)
	{
		QMessageBox::warning(this, tr("failed"), tr("The information is not defined all"), QMessageBox::Close);
	}
	else {
		bookid = ui->bookId->text();
		category = ui->category->text();
		title = ui->title->text();
		press = ui->title->text();
		author = ui->title->text();
		total_s = ui->total->text();
		total = total_s.toInt();
		stock_s = ui->stock->text();
		stock = stock_s.toInt();
		year_s = ui->year->text();
		year = year_s.toInt();
		price_s = ui->price->text();
		price = price_s.toFloat();
		query1.prepare("insert into book(bno,category,title,press,year,author,price,total,stock)" "values(:bno,:category,:title,:press,:year,:author,:price,:total,:stock)");
		query1.bindValue(":bno", bookid);
		query1.bindValue(":category", category);
		query1.bindValue(":title", title);
		query1.bindValue(":press", press);
		query1.bindValue(":year", year);
		query1.bindValue(":author", author);
		query1.bindValue(":price", price);
		query1.bindValue(":total", total);
		query1.bindValue(":stock", stock);
		if (!query1.exec())
		{
			QMessageBox::warning(this, tr("failed"), tr("fail to insert"), QMessageBox::Close);
		}
		else
		{
			QMessageBox::information(this, tr("success"), tr("succeed to insert"), QMessageBox::Ok);
			ui->bookId->clear();
			ui->category->clear();
			ui->title->clear();
			ui->press->clear();
			ui->year->clear();
			ui->author->clear();
			ui->price->clear();
			ui->total->clear();
			ui->stock->clear();
			this->close();
		}

	}
	db.close();

}


void insertbook::on_delete_2_clicked()
{
	QSqlDatabase db;
	if (!createConnection(db))
	{
		qDebug() << "register database not connect";
	}
	QSqlQuery query, query1;
	query.prepare("select * from card where bno=? ");
	query.addBindValue(ui->bookId->text());
	query.exec();
	if (query.size() == 0)
	{
		QMessageBox::warning(this, tr("failed"), tr("There is no such card,please change one"), QMessageBox::Close);
		ui->bookId->clear();
	}
	else if (ui->bookId->text() == NULL)
	{
		QMessageBox::warning(this, tr("failed"), tr("The information is not defined all"), QMessageBox::Close);
	}
	else {

		query1.prepare("delete from book where bno =? ");
		query1.addBindValue(ui->bookId->text());

		if (!query1.exec())
		{
			QMessageBox::warning(this, tr("failed"), tr("fail to delete"), QMessageBox::Close);
		}
		else
		{
			QMessageBox::information(this, tr("success"), tr("succeed to delete"), QMessageBox::Ok);
			ui->bookId->clear();
			ui->category->clear();
			ui->title->clear();
			ui->press->clear();
			ui->year->clear();
			ui->author->clear();
			ui->price->clear();
			ui->total->clear();
			ui->stock->clear();
			this->close();
		}

	}
	db.close();

}

void insertbook::on_insertBooksByList_clicked()
{
    QSqlDatabase db;
    if(!createConnection(db))
    {
        qDebug()<<"register database not connect";
    }

    QString filename = QFileDialog::getOpenFileName(this,tr("Open File"),NULL,tr("txtFile(*.txt)"));
    QSqlQuery query;
    QString temp = "load data local infile \'"+filename+"\' into table book";
    if(query.exec(temp))
         QMessageBox::information(this,tr("success"),tr("succeed to insert"),QMessageBox::Ok);
    else
        QMessageBox::warning(this,tr("failed"),tr("fail to insert"),QMessageBox::Close);
    db.close();
}

/*
void insertbook::on_insertBooksByList_clicked()
{
    QSqlDatabase db;
    if(!createConnection(db))
    {
        qDebug()<<"register database not connect";
    }
    QSqlQueryModel *model = new QSqlQueryModel;
    QString filename = QFileDialog::getOpenFileName(this);
    if(!filename.isEmpty())
    {
        QFile file(filename);
        if(!file.open(QFile::ReadOnly|QFile::Text))
        {
            QMessageBox::warning(this,tr("filed"),tr("Can not open the file"),QMessageBox::Close);
        }
        else
        {
            QTextStream in(&file);
            QString line = in.readLine();
            while(!line.isNull())
            {
                QStringList list1= line.split(",");
                int year = list1[4].toInt();
                float price = list1[6].toFloat();
                int total = list1[7].toInt();
                int stock = list1[8].toInt();

                model->setQuery(QObject::tr
                                ("insert into book values(N'%1',N'%2',N'%3',N'%4',%5,N'%6',%7,%8,%9)")
                                .arg(list1[0])
                                .arg(list1[1])
                                .arg(list1[2])
                                .arg(list1[3])
                                .arg(year)
                                .arg(list1[5])
                                .arg(price)
                                .arg(total)
                                .arg(stock)  );
                  line = in.readLine();
            }
           QMessageBox::information(this,tr("success"),tr("succeed to insert"),QMessageBox::Ok);
        }
    }
}
*/









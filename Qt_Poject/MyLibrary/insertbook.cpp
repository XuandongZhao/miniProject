#include "insertbook.h"
#include "ui_insertbook.h"
#include "Link.h"
#include "qfiledialog.h"

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
    ui->bookamount->clear();
    ui->bookauthor->clear();
    ui->bookID->clear();
    ui->bookname->clear();
    ui->bookprice->clear();
    ui->bookpublisher->clear();
    ui->booktype->clear();
    ui->bookyear->clear();
}

void insertbook::on_insertSingle_clicked()
{
    QString bookauthor,bookID,bookname,bookpublisher,booktype;
    QString bookamount_s,bookprice_s,bookyear_s;
    int bookamount, bookyear;
    float bookprice;

    QSqlDatabase db;
    if(!createConnection(db))
    {
        qDebug()<<"register database not connect";
    }
    QSqlQuery query1,query2;
    query1.prepare("select * from book where bookID =?");
    query1.addBindValue(ui->bookID->text());
    query1.exec();
    if(query1.size()>0)
    {

        QMessageBox::warning(this,tr("失败"),tr("书目已存在，请选择另一书目"),QMessageBox::Close);
        ui->bookID->clear();
    }
    else if(ui->bookamount->text()==NULL||ui->bookauthor->text()==NULL||ui->bookID->text()==NULL||
            ui->bookname->text()==NULL||ui->bookprice->text()==NULL||ui->book_publisher==NULL||
            ui->booktype->text()==NULL)
    {
        QMessageBox::warning(this,tr("失败"),tr("信息不完整"),QMessageBox::Close);
    }
    else
    {
        bookID = ui->bookID->text();
        bookname = ui->bookname->text();
        bookauthor = ui->bookauthor->text();
        bookprice_s = ui->bookprice->text();
        bookprice = bookprice_s.toFloat();
        bookamount_s = ui->bookamount->text();
        bookamount = bookamount_s.toInt();
        bookyear_s = ui->bookyear->text();
        bookyear = bookyear_s.toInt();
        bookpublisher = ui->bookpublisher->text();
        booktype = ui->booktype->text();

        query2.prepare("insert into book(bookID,bookname,bookauthor,bookprice,bookamount,bookyear,bookpublisher,booktype"
                       "values(:bookID,:bookname,:bookauthor,:bookprice,:bookamount,:bookyear,:bookpublisher,:booktype)");
        query2.bindValue(":bookID",bookID);
        query2.bindValue(":bookname",bookname);
        query2.bindValue(":bookauthor",bookauthor);
        query2.bindValue(":bookprice",bookprice);
        query2.bindValue(":bookamount",bookamount);
        query2.bindValue(":bookyear",bookyear);
        query2.bindValue(":bookpublisher",bookpublisher);
        query2.bindValue(":booktype",booktype);
        if(!query2.exec())
        {
            QMessageBox::warning(this,tr("失败"),tr("插入失败"),QMessageBox::Close);
        }
        else
        {
            QMessageBox::information(this,tr("成功"),tr("插入成功"),QMessageBox::Ok);
            ui->bookamount->clear();
            ui->bookauthor->clear();
            ui->bookID->clear();
            ui->bookname->clear();
            ui->bookprice->clear();
            ui->bookpublisher->clear();
            ui->booktype->clear();
            ui->bookyear->clear();
            this->close();
        }
    }
    db.close();
}

void insertbook::on_insertMany_clicked()
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
        QMessageBox::information(this,tr("success"),tr("insert success"),QMessageBox::Ok);
    else
        QMessageBox::warning(this,tr("failed"),tr("fail to insert"),QMessageBox::Close);
    db.close();
}















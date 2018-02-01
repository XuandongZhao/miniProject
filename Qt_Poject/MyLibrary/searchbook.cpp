#include "searchbook.h"
#include "ui_searchbook.h"
#include "Link.h"

searchbook::searchbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::searchbook)
{
    ui->setupUi(this);
}

searchbook::~searchbook()
{
    delete ui;
}

void searchbook::on_search_clicked()
{
    QString cno;
    QSqlDatabase db;
    if(!createConnection(db))
    {
        qDegug()<<"register database not connect";
    }
    QSqlQuery query1,query2;
    QString s_bookID, s_bookname, s_booktype,s_bookauthor,s_time,e_time,s_price,e_price;

    QString query_order;
    s_bookID = (ui->bookID->text()==NULL)?"%":("%"+ui->bookID->text()+"%");
    s_bookname = (ui->bookname->text()==NULL)?"%":("%"+ui->bookname->text()+"%");
    s_booktype = (ui->booktype->text()==NULL)?"%":("%"+ui->booktype->text()+"%");
    s_bookauthor = (ui->bookauthor->text()==NULL)?"%":("%"+ui->bookauthor->text()+"%");
    s_time = (ui->timestart->text()==NULL)?"0":ui->timestart->text();
    e_time = (ui->timeend->text()==NULL)?"9999":ui->timeend->text();
    s_price = (ui->pricestart->text()==NULL)?"0.00":ui->pricestart->text();
    e_price = (ui->priceend->text()==NULL)?"99999.99":ui->priceend->text();
    query_order = ui->comboBox->currentText();
    QString p1 = "select * from book where bookID like \'"+s_bookID+"\' and bookname like \'"+s_bookname
            +"\' and bookauthor like \'"+s_bookauthor+"\' and booktype like \'" + s_booktype
            +"\' and bookyear between "+s_time+"and"+e_time+"and bookprice between"+s_price
            +"and"+e_price+"order by"+query_order;
    qDebug()<<p1;
    query1.prepare(p1);
    if(!query.exec())
    {
        QMessageBox::waring(this, tr("Failed"),tr("Query failed!"),QMessageBox::Close);
        return;
    }
    qDebug()<<query1.size()<<endl;
    if(query1.size()==0)
    {
        QMessageBox::waring(this,tr("Failed"),tr("Such book does not exist"),QMessageBox::Close);
    }
    else
    {
        int i = 0;
        ui->tableWidget->setRowCount(query1.size());
        ui->tableWidget->setColumnCount(9);
        QStringList header;
        header<<"bookID"<<"bookname"<<"bookauthor"<<"bookprice"<<"bookamount"<<"bookyear"<<"bookpubisher"<<"booktype";
        ui->tableWidget->setHorizontalHeaderLabels(header);
        while(query1.next())
        {
            ui->tableWidget->setItem(i,0,new QTableWidgetItem(query1.value(0).toString()));
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(query1.value(1).toString()));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(query1.value(2).toString()));
            ui->tableWidget->setItem(i,3,new QTableWidgetItem(query1.value(3).toString()));
            ui->tableWidget->setItem(i,4,new QTableWidgetItem(query1.value(4).toString()));
            ui->tableWidget->setItem(i,5,new QTableWidgetItem(query1.value(5).toString()));
            ui->tableWidget->setItem(i,6,new QTableWidgetItem(query1.value(6).toString()));
            ui->tableWidget->setItem(i,7,new QTableWidgetItem(query1.value(7).toString()));
            ui->tableWidget->setItem(i,8,new QTableWidgetItem(query1.value(8).toString()));
            i++;
        }
    }
    db.close();
}

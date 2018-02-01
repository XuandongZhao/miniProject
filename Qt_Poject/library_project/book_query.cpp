#include "book_query.h"
#include "ui_book_query.h"
#include <QSqlTableModel>
#include <QHBoxLayout>

book_query::book_query(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::book_query)
{
    ui->setupUi(this);
}

book_query::~book_query()
{
    delete ui;
}

void book_query::on_pushButton_clicked()
{
    //书籍查询
    QString type = ui->book_type_query->text();
    QString name = ui->book_name_query->text();
    QString publish = ui->book_publish_query->text();
    QString author = ui->book_autho_query->text();
    QString year1 = ui->book_year_query->text();
    QString year2 = ui->book_year2_query->text();
    QString price1 = ui->book_price_query->text();
    QString price2 = ui->book_price2_query->text();

    int year1_ = year1.toInt();
    int year2_ = year2.toInt();
    double price1_ = price1.toDouble();
    double price2_ = price2.toDouble();
    QString item = ui->comboBox->currentText();

    if(type.isEmpty() && name.isEmpty() && publish.isEmpty() && author.isEmpty() && year1.isEmpty() && year2.isEmpty()
            && price1.isEmpty() && price2.isEmpty()){
         QMessageBox::critical(0,QObject::tr("error"),"您尚未填写任何信息");
        return;
     }
    else if((price1.isEmpty() && !price2.isEmpty())||(!price1.isEmpty() && price2.isEmpty())){
        QMessageBox::critical(0,QObject::tr("error"),"您的价格范围有误");
        return;
    }else if((year1.isEmpty() && !year2.isEmpty())||(!year1.isEmpty() && year2.isEmpty())){
        QMessageBox::critical(0,QObject::tr("error"),"您的年份范围有误");
        return;
    }

    if(year1_ > year2_ && price1_ > price2_)
    {
        QMessageBox::critical(0,QObject::tr("error"),"您的年份和价格范围有误");
                return;
    }else if(year1_ > year2_)
    {
        QMessageBox::critical(0,QObject::tr("error"),"您的年份范围有误");
                return;
    }else if(price1_ > price2_)
    {
        QMessageBox::critical(0,QObject::tr("error"),"您的价格范围有误");
        
                return;
    }

    QVector<QString>list;

    if(!type.isEmpty())
    {
        list.push_back("book_type");
        list.push_back(type);
    }
    if(!name.isEmpty()){
        list.push_back("book_name");
        list.push_back(name);
    }
    if(!publish.isEmpty())
    {
        list.push_back("book_publish");
        list.push_back(publish);
    }
    if(!year1.isEmpty())
    {
        list.push_back("years");
        list.push_back(year1);
        list.push_back(year2);
    }
    if(!price1.isEmpty())
    {
        list.push_back("price");
        list.push_back(price1);
        list.push_back(price2);
    }
    if(!author.isEmpty())
    {
        list.push_back("author");
        list.push_back(author);
    }

    int len = list.length();
    int count = 0;//计算选择类别的次数

    QString ans = "select top 50 * from book where ";
    QSqlQuery query;

    if(item.compare("类别") == 0)
    {
        item = "book_type";
    }else if(item.compare("书名") == 0)
    {
        item = "book_name";
    }else if(item.compare("出版社") == 0)
    {
        item = "bool_publish";
    }else if(item.compare("书号") == 0)
    {
        item = "bno";
    }else if(item.compare("年份") == 0)
    {
        item = "years";
    }else if(item.compare("价格") == 0)
    {
        item = "price";
    }else if(item.compare("作者") == 0)
    {
        item = "author";
    }else if(item.compare("总藏书量") == 0)
    {
        item = "num";
    }else if(item.compare("库存") == 0)
    {
        item = "num_now";
    }
    //支持模糊查询
    while(count < len)
    {
        if(count != 0)ans = ans + " and ";
        QString temp = list.front();
        QString tmp1, tmp2;
        list.pop_front();
        count++;
        if(temp.compare("years") == 0){
            tmp1 = list.front();
            list.pop_front();
            count++;
            tmp2 = list.front();
            count++;
            ans = ans + temp + " >= " + tmp1 + " and " + temp + " <= " + tmp2;

        }else if(temp.compare("price") == 0)
        {
            tmp1 = list.front();
            list.pop_front();
            count++;
            tmp2 = list.front();
            list.pop_front();
            count++;
            ans = ans + temp + " >= " + tmp1 + " and " + temp + " <= " + tmp2;
        }else
        {
            tmp1 = list.front();
            list.pop_front();
            count++;
            ans = ans + temp + " like '%" + tmp1 + "%'";

        }

    }
    ans += " order by " + item;
    query.exec(ans);
    qDebug() << ans << endl;
    if(!query.isActive())
    {    QMessageBox::critical(0,QObject::tr("error"),query.lastError().text());
             qDebug() << ans << "wrong" << endl;
    }
    QSqlQueryModel *model = new QSqlQueryModel;
    QDialog *mainDialog = new QDialog;
    QTableView *tableView = new QTableView;
    QHBoxLayout *layout = new QHBoxLayout;
    QStringList header;
    layout->addWidget(tableView);
    mainDialog->setLayout(layout);
    model->setQuery(QString(ans));
    //tableView->verticalHeader()->hide();
    //tableView->horizontalHeader()->hide();
    header<<""<<"书号"<<"类别"<<"书名"<<"出版社"<<"出版年份"<<"作者"<<"价格"<<"总藏书量"<<"库存";
    //tableView->setHorizontalHeader(header);
    tableView->resize(500,500);
    tableView->setFont(QFont("Times", 10, QFont::Black));
    tableView->setModel(model);

    //mainDialog->adjustSize();
    mainDialog->show();

}

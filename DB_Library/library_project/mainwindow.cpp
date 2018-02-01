#include "borrowcard_dialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include "ad_insert_dialog.cpp"
#include "logindialog.h"
#include "book_in_dialog.h"
#include "borrow_dialog.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlTableModel>
#include <QMessageBox>
#include <qtableview.h>
#include <QDesktopWidget>
#include <QHBoxLayout>
#include <QtSql>
#include <QFile>
#include <QString>
#include <QFileDialog>
#include "return_dialog.h"
#include "book_query.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bool sqlState =createConnection();//打开数据库，通过应用程序输出判断是否成功
    if(sqlState){
        qDebug()<<"The database is already open !";
    }
    else{
        qDebug()<<"The database open failed !";
    }
    //ui->tableViewUser->setEditTriggers(QAbstractItemView::NoEditTriggers);   //使其不可编辑
    mLoginDialog = new logindialog(this);//定义一个login对话框
    mLoginDialog->resize(400,300);
    QDesktopWidget *desk = QApplication::desktop();
    int wd = desk->width();
    int ht = desk->height();
    mLoginDialog->move((wd-mLoginDialog->width())/2, (ht - mLoginDialog->height())/2);
    mLoginDialog->setWindowFlags(mLoginDialog->windowFlags()&~Qt::WindowCloseButtonHint);//调整大小和位置
    mLoginDialog->show();
    QObject::connect(mLoginDialog, SIGNAL(passWordIsRight()), this, SLOT(showSetPage()));//将密码返回的值和主界面的显示联系在一起
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_book_in_clicked()//入库函数
{
    book_in_dialog *book_in = new book_in_dialog;
    book_in->show();
}

void MainWindow::on_book_check_clicked()//查询函数
{
    book_query *book_ = new book_query;
    book_->show();
}

void MainWindow::on_book_borrow_clicked()//借书函数
{
    borrow_dialog *borrow_book = new borrow_dialog;
    borrow_book->show();
}

void MainWindow::on_book_return_clicked()//还书函数
{
    return_dialog *return_book = new return_dialog;
    return_book->show();
}

void MainWindow::on_borrow_card_clicked()//借书证管理
{
    borrowcard_dialog *borrow_card = new borrowcard_dialog;
    borrow_card->show();
}

void MainWindow::on_ad_register_clicked()//图书管理员管理
{
    ad_insert_dialog *ad_insert = new ad_insert_dialog;
    ad_insert->show();
}

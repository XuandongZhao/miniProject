#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_booksearch_clicked()
{
    //need to link to booksearch
}

void MainWindow::on_bookborrow_clicked()
{
    //need to link to bookborrow
}

void MainWindow::on_bookreturn_clicked()
{

}

void MainWindow::on_card_clicked()
{

}

void MainWindow::on_insertbook_clicked()
{

}

void MainWindow::on_ad_register_clicked()
{

}

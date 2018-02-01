#include "mainwindow.h"
#include "interpreter.h"
#include "stdafx.h"
#include <QMessageBox>
#include <QIcon>
#include <QDebug>
#include <iostream>
#include <QPushButton>
#include <QGridLayout>
using namespace std;
BufferManager m;
Interpreter inp;
string wordline;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    isChanged = false;
    text = new QTextEdit;//中央编辑区域的实例化
    this->setCentralWidget(text);//设置到中央编辑页面。
    text->setFontPointSize(16);//修改字体大小。
    text->setMinimumSize(800,600);

    fileMenu = this->menuBar()->addMenu("文件");
    //为下拉菜单添加文件项：
    newFile = new QAction("新建",this);//实例化
    newFile->setShortcut(tr("CTRL+N"));
    fileMenu->addAction(newFile);//添加到显示
    connect(newFile,SIGNAL(triggered()),this,SLOT(on_new()));//为当前这个文件项添加一个出发事件，当前窗体响应，执行函数为on_new().

    openFile = new QAction("打开",this);//实例化
    openFile->setShortcut(tr("CTRL+O"));
    fileMenu->addAction(openFile);
    connect(openFile,SIGNAL(triggered()),this,SLOT(on_open()));

    saveFile = new QAction("保存",this);
    saveFile->setShortcut(tr("CTRL+S"));
    fileMenu->addAction(saveFile);
    connect(saveFile,SIGNAL(triggered()),this,SLOT(on_save()));

    quitFile = new QAction("退出",this);
    quitFile->setShortcut(tr("CTRL+Q"));
    fileMenu->addAction(quitFile);
    connect(quitFile,SIGNAL(triggered()),this,SLOT(on_quit()));


    editMenu =this->menuBar()->addMenu("编辑");

    copyEdit = new QAction("复制",this);
    copyEdit->setShortcut(tr("CTRL+C"));
    editMenu->addAction(copyEdit);
    connect(copyEdit,SIGNAL(triggered()),this,SLOT(on_copy()));

    pasteEdit = new QAction("粘贴",this);
    pasteEdit->setShortcut(tr("CTRL+V"));
    editMenu->addAction(pasteEdit);
    connect(pasteEdit,SIGNAL(triggered()),this,SLOT(on_paste()));

    cutEdit = new QAction("剪切",this);
    cutEdit->setShortcut(tr("CTRL+X"));
    editMenu->addAction(cutEdit);
    connect(cutEdit,SIGNAL(triggered()),this,SLOT(on_cut()));

    allSelectEdit = new QAction("全选",this);
    allSelectEdit->setShortcut(tr("CTRL+A"));
    editMenu->addAction(allSelectEdit);
    connect(allSelectEdit,SIGNAL(triggered()),this,SLOT(on_allSelect()));

    helpMenu = this->menuBar()->addMenu("帮助");

    aboutSoftware = new QAction("关于软件",this);
    helpMenu->addAction(aboutSoftware);
    connect(aboutSoftware,SIGNAL(triggered()),this,SLOT(on_aboutSoftware()));

    howToUse = new QAction("如何使用",this);
    helpMenu->addAction(howToUse);
    connect(howToUse,SIGNAL(triggered()),this,SLOT(on_howToUse()));
    connect(text,SIGNAL(textChanged()),this,SLOT(on_changed()));

    QPushButton * run = new QPushButton(this);
    QRect rc(600,550,100,30);
    run->setStyleSheet("background-color: rgb(60, 179, 170);");
    run->clearMask();
    run->setGeometry(rc);     // 设置按钮位置
    run->setText("Run"); // 设置按钮文字
    run->show();
    connect(run,SIGNAL(clicked(bool)),this,SLOT(on_run_clicked()));
}

MainWindow::~MainWindow()
{
   //delete ui;
}

void MainWindow::on_new()
{
    if(isChanged){
        QMessageBox::information(this,"提示","文件尚未保存");
    }else{
        text->setText("");//新建的话，把文本内容置空。
    }
}

void MainWindow::on_open()
{
    if(isChanged){
        QMessageBox::information(this,"提示","文件尚未保存");
    }
    else{
        fileNameString = QFileDialog::getOpenFileName(this,"打开");//当前窗体，打开文件的对话框的标题是：“打开”
        if(fileNameString==NULL){
            return ;
        }
        FILE *pf = fopen(fileNameString.toStdString().data(),"r+");//可读可写的方式打开。
        if(pf==NULL)
            return ;
        char buf[1024];
        QString str;
        while(!feof(pf)){
            fgets(buf,sizeof(buf),pf);
            str+=buf;
        }
        text->setText(str);
        fclose(pf);
    }
}

void MainWindow::on_save()
{
    fileNameString = QFileDialog::getSaveFileName(this,"保存");
    if(fileNameString==NULL)
        return ;
    FILE *pf = fopen(fileNameString.toStdString().data(),"w+");
    if(pf==NULL)
        return ;

    QString str = text->toPlainText();
    fputs(str.toStdString().data(),pf);
    fclose(pf);
    isChanged = true;
}

void MainWindow::on_quit()
{
    if(isChanged){
        QMessageBox::information(this,"提示","文件尚未保存，点击右上角×，取消保存");
    }else{
        this->close();
    }
}

void MainWindow::on_copy()
{
    text->copy();
}

void MainWindow::on_paste()
{
    text->paste();
}

void MainWindow::on_cut()
{
    text->cut();
}

void MainWindow::on_allSelect()
{
    text->selectAll();
}

void MainWindow::on_howToUse()
{
    QMessageBox::information(this,"如何使用","输入数据库命令，点击run运行");
}

void MainWindow::on_aboutSoftware()
{
    QMessageBox::information(this,"关于软件","数据库课程项目");
}

void MainWindow::on_changed()
{
    isChanged = true;

}
void MainWindow::on_run_clicked()
{
    QString list = text->toPlainText();
    qDebug() << list;
    string str;
    str = list.toStdString();
    int i;
    Interpreter R;
    i = R.interpreter(str);
}

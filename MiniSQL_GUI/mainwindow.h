#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>
#include <QFileDialog>
#include "interpreter.h"
#include "stdafx.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    bool isChanged;
    Interpreter R;
    QString fileNameString;//文件名字
    QTextEdit *text;

    QMenu *fileMenu;//文件下拉菜单

    QAction *newFile;//新建文件。
    QAction *openFile;//打开文件。
    QAction *saveFile;//保存文件。
    QAction *quitFile;//推出。

    QMenu *editMenu;//编辑菜单
    QAction *copyEdit;
    QAction *pasteEdit;
    QAction *cutEdit;
    QAction *allSelectEdit;

    QMenu *helpMenu;//帮助菜单
    QAction *aboutSoftware;
    QAction *howToUse;

private slots:
    void on_new();
    void on_open();
    void on_save();
    void on_quit();

    void on_copy();
    void on_paste();
    void on_cut();
    void on_allSelect();

    void on_howToUse();
    void on_aboutSoftware();
    void on_changed();

    void on_run_clicked();
};

#endif // MAINWINDOW_H

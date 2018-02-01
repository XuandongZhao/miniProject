#ifndef BOOK_IN_DIALOG_H
#define BOOK_IN_DIALOG_H

#include <QDialog>
#include<QFile>

namespace Ui {
class book_in_dialog;
}

class book_in_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit book_in_dialog(QWidget *parent = 0);
    ~book_in_dialog();

private slots:
    void on_onebook_in_clicked();

    void on_nbook_in_clicked();

    void readfile(QFile&);

private:
    Ui::book_in_dialog *ui;
};

#endif // BOOK_IN_DIALOG_H

#ifndef BORROW_H
#define BORROW_H

#include <QDialog>

namespace Ui {
class borrow;
}

class borrow : public QDialog
{
    Q_OBJECT

public:
    explicit borrow(QWidget *parent = 0);
    ~borrow();

private slots:
    void on_query_clicked();

    void on_borrow_clicked();

private:
    Ui::borrow *ui;
};

#endif // BORROW_H

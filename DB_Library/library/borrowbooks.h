#ifndef BORROWBOOKS_H
#define BORROWBOOKS_H

#include <QDialog>

namespace Ui {
class borrowBooks;
}

class borrowBooks : public QDialog
{
    Q_OBJECT

public:
    explicit borrowBooks(QWidget *parent = 0);
    ~borrowBooks();

private slots:
    void on_query_clicked();

    void on_exit_clicked();

    void on_clear_clicked();

    void on_borrow_clicked();

private:
    Ui::borrowBooks *ui;
};

#endif // BORROWBOOKS_H

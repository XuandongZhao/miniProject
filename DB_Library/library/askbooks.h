#ifndef ASKBOOKS_H
#define ASKBOOKS_H

#include <QDialog>

namespace Ui {
class askBooks;
}

class askBooks : public QDialog
{
    Q_OBJECT

public:
    explicit askBooks(QWidget *parent = 0);
    ~askBooks();

private slots:
    void on_Go_clicked();

private:
    Ui::askBooks *ui;
};

#endif // ASKBOOKS_H

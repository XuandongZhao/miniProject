#ifndef INSERTBOOK_H
#define INSERTBOOK_H

#include <QDialog>

namespace Ui {
class insertbook;
}

class insertbook : public QDialog
{
    Q_OBJECT

public:
    explicit insertbook(QWidget *parent = 0);
    ~insertbook();

private slots:
    void on_insertSingle_clicked();

    void on_insertMany_clicked();

    void on_exit_clicked();

    void on_clear_clicked();


private:
    Ui::insertbook *ui;
};

#endif // INSERTBOOK_H

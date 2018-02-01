#ifndef INSERTBOOK_H
#define INSERTBOOK_H

#include <QDialog>
//#include <QFile>
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
    void on_insert_clicked();

    void on_exit_clicked();

    void on_clear_clicked();

    void on_delete_2_clicked();

    void on_insertBooksByList_clicked();

  //  void readfile(QFile&);


private:
    Ui::insertbook *ui;
};

#endif // INSERTBOOK_H

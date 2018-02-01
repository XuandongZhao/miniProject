#ifndef SEARCHBOOK_H
#define SEARCHBOOK_H

#include <QDialog>

namespace Ui {
class searchbook;
}

class searchbook : public QDialog
{
    Q_OBJECT

public:
    explicit searchbook(QWidget *parent = 0);
    ~searchbook();
private slots:
    void on_search_clicked();

private:
    Ui::searchbook *ui;
};

#endif // SEARCHBOOK_H

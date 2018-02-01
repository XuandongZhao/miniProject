#ifndef AD_INSERT_DIALOG_H
#define AD_INSERT_DIALOG_H

#include <QDialog>

namespace Ui {
class ad_insert_dialog;
}

class ad_insert_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit ad_insert_dialog(QWidget *parent = 0);
    ~ad_insert_dialog();

private slots:
    void on_add_button_clicked();

    void on_delete_button_clicked();

private:
    Ui::ad_insert_dialog *ui;
};

#endif // AD_INSERT_DIALOG_H

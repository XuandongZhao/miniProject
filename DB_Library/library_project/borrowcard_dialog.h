#ifndef BORROWCARD_DIALOG_H
#define BORROWCARD_DIALOG_H

#include <QDialog>

namespace Ui {
class borrowcard_dialog;
}

class borrowcard_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit borrowcard_dialog(QWidget *parent = 0);
    ~borrowcard_dialog();

private slots:
    void on_input_button_clicked();

    void on_delete_button_clicked();

private:
    Ui::borrowcard_dialog *ui;
};

#endif // BORROWCARD_DIALOG_H

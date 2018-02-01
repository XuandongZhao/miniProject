#ifndef REGISTER_PRO_H
#define REGISTER_PRO_H

#include <QDialog>

namespace Ui {
	class Register_pro;
}

class Register_pro : public QDialog
{
	Q_OBJECT

public:
	explicit Register_pro(QWidget *parent = 0);
	~Register_pro();

	private slots:
	void on_exitBtnr_clicked();

	void on_sumBtn_clicked();

	void on_clearBtn_clicked();

private:
	Ui::Register_pro *ui;
};

#endif

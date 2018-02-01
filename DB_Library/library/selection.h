#ifndef CHOOSE_H
#define CHOOSE_H

#include <QDialog>

namespace Ui {
	class Choose;
}

class Choose : public QDialog
{
	Q_OBJECT

public:
	explicit Choose(QWidget *parent = 0);
	~Choose();

	void painEvent(QPaintEvent *event);

	private slots:
	void on_insertBooks_clicked();

	void on_askBooks_clicked();

	void on_borrowBooks_clicked();

	void on_returnbooks_clicked();

	void on_exit_clicked();

	void on_managecard_clicked();

private:
	Ui::Choose *ui;
};

#endif // CHOOSE_H

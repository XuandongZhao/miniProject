#ifndef RETURNBOOKS_H
#define RETURNBOOKS_H

#include <QDialog>

namespace Ui {
	class returnbooks;
}

class returnbooks : public QDialog
{
	Q_OBJECT
		private slots:
	void on_query_clicked();

	void on_exit_clicked();

	void on_clear_clicked();

	void on_return_2_clicked();
public:
	explicit returnbooks(QWidget *parent = 0);
	~returnbooks();

private:
	Ui::returnbooks *ui;
};

#endif // RETURNBOOKS_H

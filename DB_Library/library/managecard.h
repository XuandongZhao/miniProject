#ifndef MANAGECARD_H
#define MANAGECARD_H

#include <QDialog>

namespace Ui {
	class manageCard;
}

class manageCard : public QDialog
{
	Q_OBJECT

public:
	explicit manageCard(QWidget *parent = 0);
	~manageCard();

	private slots:
	void on_add_clicked();

	void on_exit_clicked();

	void on_clear_clicked();

	void on_delete_2_clicked();

private:
	Ui::manageCard *ui;
};

#endif // MANAGECARD_H

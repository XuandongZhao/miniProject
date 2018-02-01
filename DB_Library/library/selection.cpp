#include "selection.h"
#include "ui_selection.h"
#include "insertbook.h"
#include "managecard.h"
#include "borrowbooks.h"
#include "returnbooks.h"
#include "askbooks.h"

Choose::Choose(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::Choose)
{
	ui->setupUi(this);

	setWindowTitle(tr("Choices"));
}

Choose::~Choose()
{
	delete ui;
}

void Choose::on_exit_clicked()
{
	this->close();
}

void Choose::on_insertBooks_clicked()
{
	insertbook insert;
	insert.exec();
}

void Choose::on_managecard_clicked()
{
	manageCard card;
	card.exec();

}

void Choose::on_borrowBooks_clicked()
{
	borrowBooks borro;
	borro.exec();
}

void Choose::on_returnbooks_clicked() {
	returnbooks ret;
	ret.exec();
}

void Choose::on_askBooks_clicked() {
	askBooks askB;
	askB.exec();
}



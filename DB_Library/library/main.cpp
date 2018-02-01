#include "mainwindow.h"
#include"logindialog.h"
#include"selection.h"
#include <QApplication>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Choose w;
	//   Widget w;
	LoginDialog dlg;
	if (dlg.exec() == QDialog::Accepted)
	{
		w.show();
		return a.exec();
	}
	else
		return 0;
}

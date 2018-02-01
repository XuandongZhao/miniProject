#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql>
#include <QDebug>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QApplication>


static bool createConnection(QSqlDatabase &db)
{
	db = QSqlDatabase::addDatabase("QMYSQL");

	db.setHostName("127.0.0.1");

	db.setDatabaseName("newLibrary");
	db.setPort(3306);
	db.setUserName("root");
	db.setPassword("140921");
	if (!db.open())
	{
		//提示出错
		QMessageBox::critical(0, QObject::tr("Cannot open database"), QObject::tr("Unable to establish a database connection."), QMessageBox::Cancel);
		return false;
	}
	else
	{
		qDebug() << "open success";
		return true;
	}
}


#endif // CONNECTION_H

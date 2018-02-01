#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QObject>
#include <QSqlQueryModel>
static bool createConnection()//连接数据库
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(QString("DRIVER={SQL SERVER};"
                               "SERVER=%1;"
                               "DATABASE=%2;"
                               "UID=%3;"
                               "PWD=%4;").arg("MACHENIKE-PC")//服务器名称
                                                      .arg("library_project")//数据库名称
                                                      .arg("gao")//用户名
                                                      .arg("gtx971205"));//密码
    if(!db.open()) return false;
    QSqlQueryModel *model = new QSqlQueryModel;//使用model访问数据库
    //model->setQuery(QObject::tr("insert into Administrator values ('S','S',N'孙神','123456')"));
return true;
}

#endif // DATABASE_H

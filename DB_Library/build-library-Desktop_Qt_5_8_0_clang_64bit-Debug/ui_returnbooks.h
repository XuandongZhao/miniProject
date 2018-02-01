/********************************************************************************
** Form generated from reading UI file 'returnbooks.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RETURNBOOKS_H
#define UI_RETURNBOOKS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_returnbooks
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *card;
    QLabel *label_2;
    QLineEdit *bookid;
    QLabel *label_3;
    QTableWidget *tableWidget;
    QPushButton *query;
    QPushButton *return_2;
    QPushButton *clear;
    QPushButton *exit;

    void setupUi(QDialog *returnbooks)
    {
        if (returnbooks->objectName().isEmpty())
            returnbooks->setObjectName(QStringLiteral("returnbooks"));
        returnbooks->resize(535, 364);
        returnbooks->setStyleSheet(QStringLiteral("background-image: url(:/BingWallpaper-2017-01-22.jpg);"));
        gridLayout = new QGridLayout(returnbooks);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(returnbooks);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        card = new QLineEdit(returnbooks);
        card->setObjectName(QStringLiteral("card"));

        gridLayout->addWidget(card, 0, 2, 1, 1);

        label_2 = new QLabel(returnbooks);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        bookid = new QLineEdit(returnbooks);
        bookid->setObjectName(QStringLiteral("bookid"));

        gridLayout->addWidget(bookid, 0, 4, 1, 1);

        label_3 = new QLabel(returnbooks);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        tableWidget = new QTableWidget(returnbooks);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 1, 1, 1, 4);

        query = new QPushButton(returnbooks);
        query->setObjectName(QStringLiteral("query"));

        gridLayout->addWidget(query, 2, 2, 1, 1);

        return_2 = new QPushButton(returnbooks);
        return_2->setObjectName(QStringLiteral("return_2"));

        gridLayout->addWidget(return_2, 2, 3, 1, 2);

        clear = new QPushButton(returnbooks);
        clear->setObjectName(QStringLiteral("clear"));

        gridLayout->addWidget(clear, 3, 2, 1, 1);

        exit = new QPushButton(returnbooks);
        exit->setObjectName(QStringLiteral("exit"));

        gridLayout->addWidget(exit, 3, 3, 1, 2);


        retranslateUi(returnbooks);

        QMetaObject::connectSlotsByName(returnbooks);
    } // setupUi

    void retranslateUi(QDialog *returnbooks)
    {
        returnbooks->setWindowTitle(QApplication::translate("returnbooks", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("returnbooks", "\345\200\237\344\271\246\350\257\201\345\217\267", Q_NULLPTR));
        label_2->setText(QApplication::translate("returnbooks", "\344\271\246\345\217\267", Q_NULLPTR));
        label_3->setText(QApplication::translate("returnbooks", "\345\200\237\344\271\246\350\256\260\345\275\225", Q_NULLPTR));
        query->setText(QApplication::translate("returnbooks", "\346\237\245\350\257\242", Q_NULLPTR));
        return_2->setText(QApplication::translate("returnbooks", "\350\277\230\344\271\246", Q_NULLPTR));
        clear->setText(QApplication::translate("returnbooks", "\346\270\205\351\231\244", Q_NULLPTR));
        exit->setText(QApplication::translate("returnbooks", "\351\200\200\345\207\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class returnbooks: public Ui_returnbooks {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RETURNBOOKS_H

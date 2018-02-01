/********************************************************************************
** Form generated from reading UI file 'borrowbooks.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BORROWBOOKS_H
#define UI_BORROWBOOKS_H

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

class Ui_borrowBooks
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
    QPushButton *borrow;
    QPushButton *clear;
    QPushButton *exit;

    void setupUi(QDialog *borrowBooks)
    {
        if (borrowBooks->objectName().isEmpty())
            borrowBooks->setObjectName(QStringLiteral("borrowBooks"));
        borrowBooks->resize(526, 400);
        borrowBooks->setStyleSheet(QStringLiteral("background-image: url(:/BingWallpaper-2017-01-22.jpg);"));
        gridLayout = new QGridLayout(borrowBooks);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(borrowBooks);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        card = new QLineEdit(borrowBooks);
        card->setObjectName(QStringLiteral("card"));

        gridLayout->addWidget(card, 0, 2, 1, 1);

        label_2 = new QLabel(borrowBooks);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        bookid = new QLineEdit(borrowBooks);
        bookid->setObjectName(QStringLiteral("bookid"));

        gridLayout->addWidget(bookid, 0, 4, 1, 1);

        label_3 = new QLabel(borrowBooks);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        tableWidget = new QTableWidget(borrowBooks);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setRowCount(0);
        tableWidget->setColumnCount(0);

        gridLayout->addWidget(tableWidget, 1, 1, 1, 4);

        query = new QPushButton(borrowBooks);
        query->setObjectName(QStringLiteral("query"));

        gridLayout->addWidget(query, 2, 2, 1, 1);

        borrow = new QPushButton(borrowBooks);
        borrow->setObjectName(QStringLiteral("borrow"));

        gridLayout->addWidget(borrow, 2, 3, 1, 2);

        clear = new QPushButton(borrowBooks);
        clear->setObjectName(QStringLiteral("clear"));

        gridLayout->addWidget(clear, 3, 2, 1, 1);

        exit = new QPushButton(borrowBooks);
        exit->setObjectName(QStringLiteral("exit"));

        gridLayout->addWidget(exit, 3, 3, 1, 2);


        retranslateUi(borrowBooks);

        QMetaObject::connectSlotsByName(borrowBooks);
    } // setupUi

    void retranslateUi(QDialog *borrowBooks)
    {
        borrowBooks->setWindowTitle(QApplication::translate("borrowBooks", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("borrowBooks", "\345\200\237\344\271\246\350\257\201\345\217\267", Q_NULLPTR));
        label_2->setText(QApplication::translate("borrowBooks", "\344\271\246\345\217\267", Q_NULLPTR));
        label_3->setText(QApplication::translate("borrowBooks", "\345\200\237\344\271\246\350\256\260\345\275\225", Q_NULLPTR));
        query->setText(QApplication::translate("borrowBooks", "\346\237\245\350\257\242", Q_NULLPTR));
        borrow->setText(QApplication::translate("borrowBooks", "\345\200\237\344\271\246", Q_NULLPTR));
        clear->setText(QApplication::translate("borrowBooks", "\346\270\205\351\231\244", Q_NULLPTR));
        exit->setText(QApplication::translate("borrowBooks", "\351\200\200\345\207\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class borrowBooks: public Ui_borrowBooks {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BORROWBOOKS_H

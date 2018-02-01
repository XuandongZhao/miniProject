/********************************************************************************
** Form generated from reading UI file 'insertbook.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INSERTBOOK_H
#define UI_INSERTBOOK_H

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

QT_BEGIN_NAMESPACE

class Ui_insertbook
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *bookId;
    QLabel *label_2;
    QLineEdit *category;
    QLabel *label_3;
    QLineEdit *title;
    QLabel *label_4;
    QLineEdit *press;
    QLabel *label_5;
    QLineEdit *year;
    QLabel *label_6;
    QLineEdit *author;
    QLabel *label_7;
    QLineEdit *price;
    QLabel *label_8;
    QLineEdit *total;
    QLabel *label_9;
    QLineEdit *stock;
    QPushButton *insert;
    QPushButton *clear;
    QPushButton *delete_2;
    QPushButton *exit;
    QPushButton *insertBooksByList;

    void setupUi(QDialog *insertbook)
    {
        if (insertbook->objectName().isEmpty())
            insertbook->setObjectName(QStringLiteral("insertbook"));
        insertbook->resize(485, 376);
        insertbook->setStyleSheet(QStringLiteral("border-image: url(:/image1.jpg);"));
        gridLayout = new QGridLayout(insertbook);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(insertbook);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        bookId = new QLineEdit(insertbook);
        bookId->setObjectName(QStringLiteral("bookId"));

        gridLayout->addWidget(bookId, 0, 1, 1, 1);

        label_2 = new QLabel(insertbook);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        category = new QLineEdit(insertbook);
        category->setObjectName(QStringLiteral("category"));

        gridLayout->addWidget(category, 0, 3, 1, 1);

        label_3 = new QLabel(insertbook);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        title = new QLineEdit(insertbook);
        title->setObjectName(QStringLiteral("title"));

        gridLayout->addWidget(title, 1, 1, 1, 1);

        label_4 = new QLabel(insertbook);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 2, 1, 1);

        press = new QLineEdit(insertbook);
        press->setObjectName(QStringLiteral("press"));

        gridLayout->addWidget(press, 1, 3, 1, 1);

        label_5 = new QLabel(insertbook);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        year = new QLineEdit(insertbook);
        year->setObjectName(QStringLiteral("year"));

        gridLayout->addWidget(year, 2, 1, 1, 1);

        label_6 = new QLabel(insertbook);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 2, 2, 1, 1);

        author = new QLineEdit(insertbook);
        author->setObjectName(QStringLiteral("author"));

        gridLayout->addWidget(author, 2, 3, 1, 1);

        label_7 = new QLabel(insertbook);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        price = new QLineEdit(insertbook);
        price->setObjectName(QStringLiteral("price"));

        gridLayout->addWidget(price, 3, 1, 1, 1);

        label_8 = new QLabel(insertbook);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 3, 2, 1, 1);

        total = new QLineEdit(insertbook);
        total->setObjectName(QStringLiteral("total"));

        gridLayout->addWidget(total, 3, 3, 1, 1);

        label_9 = new QLabel(insertbook);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 4, 0, 1, 1);

        stock = new QLineEdit(insertbook);
        stock->setObjectName(QStringLiteral("stock"));

        gridLayout->addWidget(stock, 4, 1, 1, 1);

        insert = new QPushButton(insertbook);
        insert->setObjectName(QStringLiteral("insert"));

        gridLayout->addWidget(insert, 5, 1, 1, 1);

        clear = new QPushButton(insertbook);
        clear->setObjectName(QStringLiteral("clear"));

        gridLayout->addWidget(clear, 6, 1, 1, 1);

        delete_2 = new QPushButton(insertbook);
        delete_2->setObjectName(QStringLiteral("delete_2"));

        gridLayout->addWidget(delete_2, 5, 3, 1, 1);

        exit = new QPushButton(insertbook);
        exit->setObjectName(QStringLiteral("exit"));

        gridLayout->addWidget(exit, 6, 3, 1, 1);

        insertBooksByList = new QPushButton(insertbook);
        insertBooksByList->setObjectName(QStringLiteral("insertBooksByList"));

        gridLayout->addWidget(insertBooksByList, 4, 3, 1, 1);


        retranslateUi(insertbook);

        QMetaObject::connectSlotsByName(insertbook);
    } // setupUi

    void retranslateUi(QDialog *insertbook)
    {
        insertbook->setWindowTitle(QApplication::translate("insertbook", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("insertbook", "\344\271\246\345\217\267", Q_NULLPTR));
        label_2->setText(QApplication::translate("insertbook", "\347\261\273\345\210\253", Q_NULLPTR));
        label_3->setText(QApplication::translate("insertbook", "\344\271\246\345\220\215", Q_NULLPTR));
        label_4->setText(QApplication::translate("insertbook", "\345\207\272\347\211\210\347\244\276", Q_NULLPTR));
        label_5->setText(QApplication::translate("insertbook", "\345\207\272\347\211\210\346\227\266\351\227\264", Q_NULLPTR));
        label_6->setText(QApplication::translate("insertbook", "\344\275\234\350\200\205", Q_NULLPTR));
        label_7->setText(QApplication::translate("insertbook", "\344\273\267\346\240\274", Q_NULLPTR));
        label_8->setText(QApplication::translate("insertbook", "\346\200\273\351\207\217", Q_NULLPTR));
        label_9->setText(QApplication::translate("insertbook", "\345\272\223\345\255\230", Q_NULLPTR));
        insert->setText(QApplication::translate("insertbook", "\345\215\225\345\206\214\345\205\245\345\272\223", Q_NULLPTR));
        clear->setText(QApplication::translate("insertbook", "\346\270\205\351\231\244", Q_NULLPTR));
        delete_2->setText(QApplication::translate("insertbook", "\345\210\240\351\231\244", Q_NULLPTR));
        exit->setText(QApplication::translate("insertbook", "\351\200\200\345\207\272", Q_NULLPTR));
        insertBooksByList->setText(QApplication::translate("insertbook", "\345\244\232\345\206\214\345\205\245\345\272\223", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class insertbook: public Ui_insertbook {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INSERTBOOK_H

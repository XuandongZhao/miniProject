/********************************************************************************
** Form generated from reading UI file 'askbooks.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASKBOOKS_H
#define UI_ASKBOOKS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_askBooks
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *category;
    QLabel *label_2;
    QLineEdit *title;
    QLabel *label_3;
    QLineEdit *press;
    QLabel *label_9;
    QLineEdit *author;
    QLabel *label_4;
    QLineEdit *s_year;
    QFrame *line;
    QLineEdit *t_year;
    QLabel *label_5;
    QLineEdit *s_price;
    QFrame *line_2;
    QLineEdit *t_price;
    QTableWidget *tableWidget;
    QLabel *label_8;
    QComboBox *comboBox;
    QPushButton *Go;

    void setupUi(QDialog *askBooks)
    {
        if (askBooks->objectName().isEmpty())
            askBooks->setObjectName(QStringLiteral("askBooks"));
        askBooks->resize(614, 457);
        askBooks->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(askBooks);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(askBooks);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        category = new QLineEdit(askBooks);
        category->setObjectName(QStringLiteral("category"));

        gridLayout->addWidget(category, 0, 1, 1, 1);

        label_2 = new QLabel(askBooks);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 3, 1, 1);

        title = new QLineEdit(askBooks);
        title->setObjectName(QStringLiteral("title"));

        gridLayout->addWidget(title, 0, 4, 1, 1);

        label_3 = new QLabel(askBooks);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        press = new QLineEdit(askBooks);
        press->setObjectName(QStringLiteral("press"));

        gridLayout->addWidget(press, 1, 1, 1, 1);

        label_9 = new QLabel(askBooks);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout->addWidget(label_9, 1, 3, 1, 1);

        author = new QLineEdit(askBooks);
        author->setObjectName(QStringLiteral("author"));

        gridLayout->addWidget(author, 1, 4, 1, 1);

        label_4 = new QLabel(askBooks);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        s_year = new QLineEdit(askBooks);
        s_year->setObjectName(QStringLiteral("s_year"));

        gridLayout->addWidget(s_year, 2, 1, 1, 1);

        line = new QFrame(askBooks);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line, 2, 2, 1, 1);

        t_year = new QLineEdit(askBooks);
        t_year->setObjectName(QStringLiteral("t_year"));

        gridLayout->addWidget(t_year, 2, 3, 1, 2);

        label_5 = new QLabel(askBooks);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        s_price = new QLineEdit(askBooks);
        s_price->setObjectName(QStringLiteral("s_price"));

        gridLayout->addWidget(s_price, 3, 1, 1, 1);

        line_2 = new QFrame(askBooks);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_2, 3, 2, 1, 1);

        t_price = new QLineEdit(askBooks);
        t_price->setObjectName(QStringLiteral("t_price"));

        gridLayout->addWidget(t_price, 3, 3, 1, 2);

        tableWidget = new QTableWidget(askBooks);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 6, 0, 1, 5);

        label_8 = new QLabel(askBooks);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout->addWidget(label_8, 4, 0, 1, 1);

        comboBox = new QComboBox(askBooks);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 4, 1, 1, 1);

        Go = new QPushButton(askBooks);
        Go->setObjectName(QStringLiteral("Go"));

        gridLayout->addWidget(Go, 5, 2, 1, 1);


        retranslateUi(askBooks);

        QMetaObject::connectSlotsByName(askBooks);
    } // setupUi

    void retranslateUi(QDialog *askBooks)
    {
        askBooks->setWindowTitle(QApplication::translate("askBooks", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("askBooks", "\347\261\273\345\210\253", Q_NULLPTR));
        label_2->setText(QApplication::translate("askBooks", "\344\271\246\345\220\215", Q_NULLPTR));
        label_3->setText(QApplication::translate("askBooks", "\345\207\272\347\211\210\347\244\276", Q_NULLPTR));
        label_9->setText(QApplication::translate("askBooks", "\344\275\234\350\200\205", Q_NULLPTR));
        label_4->setText(QApplication::translate("askBooks", "\346\227\266\351\227\264", Q_NULLPTR));
        label_5->setText(QApplication::translate("askBooks", "\344\273\267\346\240\274", Q_NULLPTR));
        label_8->setText(QApplication::translate("askBooks", "\346\230\276\347\244\272\346\216\222\345\272\217", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("askBooks", "bno", Q_NULLPTR)
         << QApplication::translate("askBooks", "category", Q_NULLPTR)
         << QApplication::translate("askBooks", "press", Q_NULLPTR)
         << QApplication::translate("askBooks", "year", Q_NULLPTR)
         << QApplication::translate("askBooks", "price", Q_NULLPTR)
         << QApplication::translate("askBooks", "stock", Q_NULLPTR)
        );
        Go->setText(QApplication::translate("askBooks", "\346\237\245\350\257\242", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class askBooks: public Ui_askBooks {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASKBOOKS_H

/********************************************************************************
** Form generated from reading UI file 'managecard.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGECARD_H
#define UI_MANAGECARD_H

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

class Ui_manageCard
{
public:
    QGridLayout *gridLayout;
    QLabel *card_3;
    QLineEdit *card;
    QLabel *name_3;
    QLineEdit *name;
    QLabel *department_3;
    QLineEdit *department;
    QLabel *type_3;
    QLineEdit *type;
    QPushButton *delete_2;
    QPushButton *exit;
    QPushButton *add;
    QPushButton *clear;

    void setupUi(QDialog *manageCard)
    {
        if (manageCard->objectName().isEmpty())
            manageCard->setObjectName(QStringLiteral("manageCard"));
        manageCard->resize(446, 319);
        manageCard->setStyleSheet(QStringLiteral("background-image: url(:/image1.jpg);"));
        gridLayout = new QGridLayout(manageCard);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        card_3 = new QLabel(manageCard);
        card_3->setObjectName(QStringLiteral("card_3"));

        gridLayout->addWidget(card_3, 0, 0, 1, 1);

        card = new QLineEdit(manageCard);
        card->setObjectName(QStringLiteral("card"));

        gridLayout->addWidget(card, 0, 1, 1, 2);

        name_3 = new QLabel(manageCard);
        name_3->setObjectName(QStringLiteral("name_3"));

        gridLayout->addWidget(name_3, 1, 0, 1, 1);

        name = new QLineEdit(manageCard);
        name->setObjectName(QStringLiteral("name"));

        gridLayout->addWidget(name, 1, 1, 1, 2);

        department_3 = new QLabel(manageCard);
        department_3->setObjectName(QStringLiteral("department_3"));

        gridLayout->addWidget(department_3, 2, 0, 1, 1);

        department = new QLineEdit(manageCard);
        department->setObjectName(QStringLiteral("department"));

        gridLayout->addWidget(department, 2, 1, 1, 2);

        type_3 = new QLabel(manageCard);
        type_3->setObjectName(QStringLiteral("type_3"));

        gridLayout->addWidget(type_3, 3, 0, 1, 1);

        type = new QLineEdit(manageCard);
        type->setObjectName(QStringLiteral("type"));

        gridLayout->addWidget(type, 3, 1, 1, 2);

        delete_2 = new QPushButton(manageCard);
        delete_2->setObjectName(QStringLiteral("delete_2"));

        gridLayout->addWidget(delete_2, 4, 2, 1, 1);

        exit = new QPushButton(manageCard);
        exit->setObjectName(QStringLiteral("exit"));

        gridLayout->addWidget(exit, 5, 2, 1, 1);

        add = new QPushButton(manageCard);
        add->setObjectName(QStringLiteral("add"));

        gridLayout->addWidget(add, 4, 0, 1, 1);

        clear = new QPushButton(manageCard);
        clear->setObjectName(QStringLiteral("clear"));

        gridLayout->addWidget(clear, 5, 0, 1, 1);


        retranslateUi(manageCard);

        QMetaObject::connectSlotsByName(manageCard);
    } // setupUi

    void retranslateUi(QDialog *manageCard)
    {
        manageCard->setWindowTitle(QApplication::translate("manageCard", "Dialog", Q_NULLPTR));
        card_3->setText(QApplication::translate("manageCard", "\345\200\237\344\271\246\350\257\201\345\217\267", Q_NULLPTR));
        name_3->setText(QApplication::translate("manageCard", "\345\247\223\345\220\215", Q_NULLPTR));
        department_3->setText(QApplication::translate("manageCard", "\351\231\242\347\263\273", Q_NULLPTR));
        type_3->setText(QApplication::translate("manageCard", "\347\261\273\345\210\253", Q_NULLPTR));
        delete_2->setText(QApplication::translate("manageCard", "\345\210\240\351\231\244", Q_NULLPTR));
        exit->setText(QApplication::translate("manageCard", "\351\200\200\345\207\272", Q_NULLPTR));
        add->setText(QApplication::translate("manageCard", "\346\267\273\345\212\240", Q_NULLPTR));
        clear->setText(QApplication::translate("manageCard", "\346\270\205\351\231\244", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class manageCard: public Ui_manageCard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGECARD_H

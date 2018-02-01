/********************************************************************************
** Form generated from reading UI file 'register_pro.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_PRO_H
#define UI_REGISTER_PRO_H

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

class Ui_Register_pro
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *logIdLE_R;
    QLabel *label_2;
    QLineEdit *logPwdLE_R;
    QLabel *label_5;
    QLineEdit *logPwdSure;
    QLabel *label_3;
    QLineEdit *nameLE;
    QLabel *label_4;
    QLineEdit *telLE;
    QPushButton *sumBtn;
    QPushButton *exitBtnr;
    QPushButton *clearBtn;

    void setupUi(QDialog *Register_pro)
    {
        if (Register_pro->objectName().isEmpty())
            Register_pro->setObjectName(QStringLiteral("Register_pro"));
        Register_pro->resize(440, 312);
        Register_pro->setStyleSheet(QStringLiteral("background-image: url(:/image1.jpg);"));
        gridLayout = new QGridLayout(Register_pro);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(Register_pro);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        logIdLE_R = new QLineEdit(Register_pro);
        logIdLE_R->setObjectName(QStringLiteral("logIdLE_R"));

        gridLayout->addWidget(logIdLE_R, 0, 1, 1, 2);

        label_2 = new QLabel(Register_pro);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        logPwdLE_R = new QLineEdit(Register_pro);
        logPwdLE_R->setObjectName(QStringLiteral("logPwdLE_R"));

        gridLayout->addWidget(logPwdLE_R, 1, 1, 1, 2);

        label_5 = new QLabel(Register_pro);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        logPwdSure = new QLineEdit(Register_pro);
        logPwdSure->setObjectName(QStringLiteral("logPwdSure"));

        gridLayout->addWidget(logPwdSure, 2, 1, 1, 2);

        label_3 = new QLabel(Register_pro);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        nameLE = new QLineEdit(Register_pro);
        nameLE->setObjectName(QStringLiteral("nameLE"));

        gridLayout->addWidget(nameLE, 3, 1, 1, 2);

        label_4 = new QLabel(Register_pro);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        telLE = new QLineEdit(Register_pro);
        telLE->setObjectName(QStringLiteral("telLE"));

        gridLayout->addWidget(telLE, 4, 1, 1, 2);

        sumBtn = new QPushButton(Register_pro);
        sumBtn->setObjectName(QStringLiteral("sumBtn"));

        gridLayout->addWidget(sumBtn, 5, 0, 1, 1);

        exitBtnr = new QPushButton(Register_pro);
        exitBtnr->setObjectName(QStringLiteral("exitBtnr"));

        gridLayout->addWidget(exitBtnr, 5, 1, 1, 1);

        clearBtn = new QPushButton(Register_pro);
        clearBtn->setObjectName(QStringLiteral("clearBtn"));

        gridLayout->addWidget(clearBtn, 5, 2, 1, 1);


        retranslateUi(Register_pro);

        QMetaObject::connectSlotsByName(Register_pro);
    } // setupUi

    void retranslateUi(QDialog *Register_pro)
    {
        Register_pro->setWindowTitle(QApplication::translate("Register_pro", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("Register_pro", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        label_2->setText(QApplication::translate("Register_pro", "\345\257\206\347\240\201", Q_NULLPTR));
        label_5->setText(QApplication::translate("Register_pro", "\351\207\215\346\226\260\350\276\223\345\205\245\345\257\206\347\240\201", Q_NULLPTR));
        label_3->setText(QApplication::translate("Register_pro", "\345\247\223\345\220\215", Q_NULLPTR));
        label_4->setText(QApplication::translate("Register_pro", "\347\224\265\350\257\235\345\217\267\347\240\201", Q_NULLPTR));
        sumBtn->setText(QApplication::translate("Register_pro", "\347\231\273\351\231\206", Q_NULLPTR));
        exitBtnr->setText(QApplication::translate("Register_pro", "\351\200\200\345\207\272", Q_NULLPTR));
        clearBtn->setText(QApplication::translate("Register_pro", "\351\207\215\347\275\256", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Register_pro: public Ui_Register_pro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_PRO_H

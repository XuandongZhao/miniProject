/********************************************************************************
** Form generated from reading UI file 'selection.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTION_H
#define UI_SELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_Choose
{
public:
    QPushButton *insertBooks;
    QPushButton *borrowBooks;
    QPushButton *returnbooks;
    QTextBrowser *textBrowser;
    QPushButton *exit;
    QPushButton *askBooks;
    QPushButton *managecard;
    QTextBrowser *textBrowser_2;

    void setupUi(QDialog *Choose)
    {
        if (Choose->objectName().isEmpty())
            Choose->setObjectName(QStringLiteral("Choose"));
        Choose->resize(408, 282);
        Choose->setStyleSheet(QStringLiteral("background-image: url(:/1.jpg);"));
        insertBooks = new QPushButton(Choose);
        insertBooks->setObjectName(QStringLiteral("insertBooks"));
        insertBooks->setGeometry(QRect(60, 180, 94, 32));
        insertBooks->setStyleSheet(QStringLiteral("selection-color: rgb(255, 255, 255);"));
        borrowBooks = new QPushButton(Choose);
        borrowBooks->setObjectName(QStringLiteral("borrowBooks"));
        borrowBooks->setGeometry(QRect(60, 210, 94, 32));
        returnbooks = new QPushButton(Choose);
        returnbooks->setObjectName(QStringLiteral("returnbooks"));
        returnbooks->setGeometry(QRect(230, 210, 94, 32));
        textBrowser = new QTextBrowser(Choose);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(100, 10, 201, 31));
        exit = new QPushButton(Choose);
        exit->setObjectName(QStringLiteral("exit"));
        exit->setGeometry(QRect(230, 240, 94, 32));
        askBooks = new QPushButton(Choose);
        askBooks->setObjectName(QStringLiteral("askBooks"));
        askBooks->setGeometry(QRect(230, 180, 94, 32));
        managecard = new QPushButton(Choose);
        managecard->setObjectName(QStringLiteral("managecard"));
        managecard->setGeometry(QRect(50, 240, 107, 32));
        textBrowser_2 = new QTextBrowser(Choose);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(10, 40, 381, 141));

        retranslateUi(Choose);

        QMetaObject::connectSlotsByName(Choose);
    } // setupUi

    void retranslateUi(QDialog *Choose)
    {
        Choose->setWindowTitle(QApplication::translate("Choose", "Dialog", Q_NULLPTR));
        insertBooks->setText(QApplication::translate("Choose", "\345\233\276\344\271\246\347\256\241\347\220\206", Q_NULLPTR));
        borrowBooks->setText(QApplication::translate("Choose", "\345\233\276\344\271\246\345\200\237\351\230\205", Q_NULLPTR));
        returnbooks->setText(QApplication::translate("Choose", "\345\233\276\344\271\246\345\275\222\350\277\230", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate("Choose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'.SF NS Text'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:14pt; font-weight:600; color:#0080ff;\">\346\254\242\350\277\216\344\275\277\347\224\250\345\233\276\344\271\246\347\256\241\347\220\206\347\263\273\347\273\237</span></p></body></html>", Q_NULLPTR));
        exit->setText(QApplication::translate("Choose", "\351\200\200\345\207\272\347\263\273\347\273\237", Q_NULLPTR));
        askBooks->setText(QApplication::translate("Choose", "\345\233\276\344\271\246\346\237\245\350\257\242", Q_NULLPTR));
        managecard->setText(QApplication::translate("Choose", "\345\200\237\344\271\246\350\257\201\347\256\241\347\220\206", Q_NULLPTR));
        textBrowser_2->setHtml(QApplication::translate("Choose", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'.SF NS Text'; font-size:13pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/new/prefix1/2.png\" /></p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Choose: public Ui_Choose {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTION_H

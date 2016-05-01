/********************************************************************************
** Form generated from reading UI file 'ready.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_READY_H
#define UI_READY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ready
{
public:
    QPushButton *readyButton;
    QTextBrowser *titleText;
    QLabel *label;
    QPushButton *leaveButton;

    void setupUi(QWidget *ready)
    {
        if (ready->objectName().isEmpty())
            ready->setObjectName(QStringLiteral("ready"));
        ready->resize(400, 300);
        readyButton = new QPushButton(ready);
        readyButton->setObjectName(QStringLiteral("readyButton"));
        readyButton->setGeometry(QRect(40, 70, 311, 26));
        titleText = new QTextBrowser(ready);
        titleText->setObjectName(QStringLiteral("titleText"));
        titleText->setGeometry(QRect(40, 20, 311, 41));
        label = new QLabel(ready);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(110, 140, 171, 17));
        label->setAlignment(Qt::AlignCenter);
        leaveButton = new QPushButton(ready);
        leaveButton->setObjectName(QStringLiteral("leaveButton"));
        leaveButton->setGeometry(QRect(40, 100, 311, 26));

        retranslateUi(ready);

        QMetaObject::connectSlotsByName(ready);
    } // setupUi

    void retranslateUi(QWidget *ready)
    {
        ready->setWindowTitle(QApplication::translate("ready", "Form", 0));
        readyButton->setText(QApplication::translate("ready", "Ready to Play", 0));
        titleText->setHtml(QApplication::translate("ready", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#eb1818;\">WerewolfPaxos</span></p></body></html>", 0));
        label->setText(QString());
        leaveButton->setText(QApplication::translate("ready", "Leave Game", 0));
    } // retranslateUi

};

namespace Ui {
    class ready: public Ui_ready {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_READY_H

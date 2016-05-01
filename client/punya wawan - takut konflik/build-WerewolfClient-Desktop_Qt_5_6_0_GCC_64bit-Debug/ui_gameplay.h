/********************************************************************************
** Form generated from reading UI file 'gameplay.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEPLAY_H
#define UI_GAMEPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gameplay
{
public:
    QWidget *centralwidget;
    QTableWidget *listPlayerTable;
    QTextBrowser *titleText;
    QLabel *voteLabel;
    QLineEdit *voteEdit;
    QPushButton *killButton;
    QFrame *line;
    QLabel *listLabel;
    QLabel *usernameLabel;
    QLabel *idLabel;
    QLabel *roleLabel;
    QLabel *phaseLabel;
    QLabel *daysLabel;
    QLabel *friendLabel;
    QLabel *usernameText;
    QFrame *line_2;
    QLabel *idText;
    QLabel *roleText;
    QLabel *phaseText;
    QLabel *daysText;
    QLabel *friendText;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *gameplay)
    {
        if (gameplay->objectName().isEmpty())
            gameplay->setObjectName(QStringLiteral("gameplay"));
        gameplay->resize(538, 401);
        centralwidget = new QWidget(gameplay);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        listPlayerTable = new QTableWidget(centralwidget);
        listPlayerTable->setObjectName(QStringLiteral("listPlayerTable"));
        listPlayerTable->setGeometry(QRect(10, 210, 371, 151));
        titleText = new QTextBrowser(centralwidget);
        titleText->setObjectName(QStringLiteral("titleText"));
        titleText->setGeometry(QRect(20, 10, 501, 41));
        voteLabel = new QLabel(centralwidget);
        voteLabel->setObjectName(QStringLiteral("voteLabel"));
        voteLabel->setGeometry(QRect(390, 250, 81, 17));
        voteEdit = new QLineEdit(centralwidget);
        voteEdit->setObjectName(QStringLiteral("voteEdit"));
        voteEdit->setGeometry(QRect(390, 270, 141, 27));
        killButton = new QPushButton(centralwidget);
        killButton->setObjectName(QStringLiteral("killButton"));
        killButton->setGeometry(QRect(390, 300, 141, 61));
        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 170, 521, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        listLabel = new QLabel(centralwidget);
        listLabel->setObjectName(QStringLiteral("listLabel"));
        listLabel->setGeometry(QRect(10, 190, 111, 17));
        usernameLabel = new QLabel(centralwidget);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));
        usernameLabel->setGeometry(QRect(10, 60, 101, 17));
        idLabel = new QLabel(centralwidget);
        idLabel->setObjectName(QStringLiteral("idLabel"));
        idLabel->setGeometry(QRect(10, 80, 101, 17));
        roleLabel = new QLabel(centralwidget);
        roleLabel->setObjectName(QStringLiteral("roleLabel"));
        roleLabel->setGeometry(QRect(10, 100, 101, 17));
        phaseLabel = new QLabel(centralwidget);
        phaseLabel->setObjectName(QStringLiteral("phaseLabel"));
        phaseLabel->setGeometry(QRect(280, 60, 101, 17));
        daysLabel = new QLabel(centralwidget);
        daysLabel->setObjectName(QStringLiteral("daysLabel"));
        daysLabel->setGeometry(QRect(280, 80, 101, 17));
        friendLabel = new QLabel(centralwidget);
        friendLabel->setObjectName(QStringLiteral("friendLabel"));
        friendLabel->setGeometry(QRect(280, 100, 101, 17));
        usernameText = new QLabel(centralwidget);
        usernameText->setObjectName(QStringLiteral("usernameText"));
        usernameText->setGeometry(QRect(100, 60, 161, 17));
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(270, 60, 3, 61));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        idText = new QLabel(centralwidget);
        idText->setObjectName(QStringLiteral("idText"));
        idText->setGeometry(QRect(100, 80, 161, 17));
        roleText = new QLabel(centralwidget);
        roleText->setObjectName(QStringLiteral("roleText"));
        roleText->setGeometry(QRect(100, 100, 161, 17));
        phaseText = new QLabel(centralwidget);
        phaseText->setObjectName(QStringLiteral("phaseText"));
        phaseText->setGeometry(QRect(350, 60, 161, 17));
        daysText = new QLabel(centralwidget);
        daysText->setObjectName(QStringLiteral("daysText"));
        daysText->setGeometry(QRect(350, 80, 161, 17));
        friendText = new QLabel(centralwidget);
        friendText->setObjectName(QStringLiteral("friendText"));
        friendText->setGeometry(QRect(350, 100, 161, 17));
        gameplay->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(gameplay);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        gameplay->setStatusBar(statusbar);

        retranslateUi(gameplay);

        QMetaObject::connectSlotsByName(gameplay);
    } // setupUi

    void retranslateUi(QMainWindow *gameplay)
    {
        gameplay->setWindowTitle(QApplication::translate("gameplay", "MainWindow", 0));
        titleText->setHtml(QApplication::translate("gameplay", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#eb1818;\">WerewolfPaxos</span></p></body></html>", 0));
        voteLabel->setText(QApplication::translate("gameplay", "Vote to Kill", 0));
        killButton->setText(QApplication::translate("gameplay", "KILL!", 0));
        listLabel->setText(QApplication::translate("gameplay", "Client List", 0));
        usernameLabel->setText(QApplication::translate("gameplay", "Username", 0));
        idLabel->setText(QApplication::translate("gameplay", "Player ID", 0));
        roleLabel->setText(QApplication::translate("gameplay", "Role", 0));
        phaseLabel->setText(QApplication::translate("gameplay", "Phase", 0));
        daysLabel->setText(QApplication::translate("gameplay", "Days", 0));
        friendLabel->setText(QApplication::translate("gameplay", "Friend", 0));
        usernameText->setText(QString());
        idText->setText(QString());
        roleText->setText(QString());
        phaseText->setText(QString());
        daysText->setText(QString());
        friendText->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class gameplay: public Ui_gameplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEPLAY_H

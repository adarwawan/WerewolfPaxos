/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QWidget *centralWidget;
    QPushButton *buttonPlay;
    QLineEdit *username;
    QLineEdit *address;
    QLineEdit *tcp_port;
    QLineEdit *udp_port;
    QLabel *username_label;
    QLabel *address_label;
    QLabel *server_port_label;
    QLabel *client_port_label;
    QTextBrowser *textBrowser;
    QPushButton *buttonReady;
    QLabel *labelReady;

    void setupUi(QMainWindow *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName(QStringLiteral("login"));
        login->resize(400, 300);
        centralWidget = new QWidget(login);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        buttonPlay = new QPushButton(centralWidget);
        buttonPlay->setObjectName(QStringLiteral("buttonPlay"));
        buttonPlay->setGeometry(QRect(280, 260, 97, 26));
        username = new QLineEdit(centralWidget);
        username->setObjectName(QStringLiteral("username"));
        username->setGeometry(QRect(160, 100, 181, 27));
        address = new QLineEdit(centralWidget);
        address->setObjectName(QStringLiteral("address"));
        address->setGeometry(QRect(160, 130, 181, 27));
        tcp_port = new QLineEdit(centralWidget);
        tcp_port->setObjectName(QStringLiteral("tcp_port"));
        tcp_port->setGeometry(QRect(160, 160, 181, 27));
        udp_port = new QLineEdit(centralWidget);
        udp_port->setObjectName(QStringLiteral("udp_port"));
        udp_port->setGeometry(QRect(160, 190, 181, 27));
        username_label = new QLabel(centralWidget);
        username_label->setObjectName(QStringLiteral("username_label"));
        username_label->setGeometry(QRect(70, 100, 71, 20));
        username_label->setLayoutDirection(Qt::RightToLeft);
        username_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        address_label = new QLabel(centralWidget);
        address_label->setObjectName(QStringLiteral("address_label"));
        address_label->setGeometry(QRect(40, 130, 101, 20));
        address_label->setLayoutDirection(Qt::RightToLeft);
        address_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        server_port_label = new QLabel(centralWidget);
        server_port_label->setObjectName(QStringLiteral("server_port_label"));
        server_port_label->setGeometry(QRect(60, 160, 81, 20));
        server_port_label->setLayoutDirection(Qt::RightToLeft);
        server_port_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        client_port_label = new QLabel(centralWidget);
        client_port_label->setObjectName(QStringLiteral("client_port_label"));
        client_port_label->setGeometry(QRect(60, 190, 81, 20));
        client_port_label->setLayoutDirection(Qt::RightToLeft);
        client_port_label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(45, 10, 311, 41));
        buttonReady = new QPushButton(centralWidget);
        buttonReady->setObjectName(QStringLiteral("buttonReady"));
        buttonReady->setGeometry(QRect(20, 260, 97, 26));
        labelReady = new QLabel(centralWidget);
        labelReady->setObjectName(QStringLiteral("labelReady"));
        labelReady->setGeometry(QRect(136, 240, 231, 20));
        labelReady->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        login->setCentralWidget(centralWidget);

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QMainWindow *login)
    {
        login->setWindowTitle(QApplication::translate("login", "login", 0));
        buttonPlay->setText(QApplication::translate("login", "Login", 0));
        username->setText(QString());
        address->setText(QApplication::translate("login", "localhost", 0));
        tcp_port->setText(QApplication::translate("login", "55555", 0));
        udp_port->setText(QApplication::translate("login", "1231", 0));
        username_label->setText(QApplication::translate("login", "Username", 0));
        address_label->setText(QApplication::translate("login", "Server Address", 0));
        server_port_label->setText(QApplication::translate("login", "Server Port", 0));
        client_port_label->setText(QApplication::translate("login", "Client Port", 0));
        textBrowser->setHtml(QApplication::translate("login", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#eb1818;\">WerewolfPaxos</span></p></body></html>", 0));
        buttonReady->setText(QApplication::translate("login", "Ready", 0));
        labelReady->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H

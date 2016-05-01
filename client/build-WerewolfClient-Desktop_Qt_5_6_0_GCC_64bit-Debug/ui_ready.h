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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ready
{
public:
    QLabel *label;

    void setupUi(QWidget *ready)
    {
        if (ready->objectName().isEmpty())
            ready->setObjectName(QStringLiteral("ready"));
        ready->resize(400, 300);
        label = new QLabel(ready);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(170, 140, 211, 17));

        retranslateUi(ready);

        QMetaObject::connectSlotsByName(ready);
    } // setupUi

    void retranslateUi(QWidget *ready)
    {
        ready->setWindowTitle(QApplication::translate("ready", "Form", 0));
        label->setText(QApplication::translate("ready", "EAAAAAAAAAAAA", 0));
    } // retranslateUi

};

namespace Ui {
    class ready: public Ui_ready {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_READY_H

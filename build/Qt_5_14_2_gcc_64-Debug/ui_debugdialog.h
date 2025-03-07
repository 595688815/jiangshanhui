/********************************************************************************
** Form generated from reading UI file 'debugdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEBUGDIALOG_H
#define UI_DEBUGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DebugDialog
{
public:
    QPushButton *pushButton;
    QTextEdit *textEdit;
    QPushButton *RefreshBtn;

    void setupUi(QWidget *DebugDialog)
    {
        if (DebugDialog->objectName().isEmpty())
            DebugDialog->setObjectName(QString::fromUtf8("DebugDialog"));
        DebugDialog->resize(940, 649);
        pushButton = new QPushButton(DebugDialog);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 20, 89, 25));
        textEdit = new QTextEdit(DebugDialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(130, 10, 230, 621));
        RefreshBtn = new QPushButton(DebugDialog);
        RefreshBtn->setObjectName(QString::fromUtf8("RefreshBtn"));
        RefreshBtn->setGeometry(QRect(30, 60, 89, 25));

        retranslateUi(DebugDialog);

        QMetaObject::connectSlotsByName(DebugDialog);
    } // setupUi

    void retranslateUi(QWidget *DebugDialog)
    {
        DebugDialog->setWindowTitle(QCoreApplication::translate("DebugDialog", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("DebugDialog", "Debug", nullptr));
        RefreshBtn->setText(QCoreApplication::translate("DebugDialog", "Refresh", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DebugDialog: public Ui_DebugDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEBUGDIALOG_H

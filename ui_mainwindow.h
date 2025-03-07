/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *DebugBtn;
    QPushButton *DebugBtn_2;
    QPushButton *DebugBtn_3;
    QPushButton *DebugBtn_4;
    QPushButton *DebugBtn_5;
    QPushButton *DebugBtn_6;
    QPushButton *DebugBtn_7;
    QPushButton *DebugBtn_8;
    QTextEdit *textEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        DebugBtn = new QPushButton(centralwidget);
        DebugBtn->setObjectName(QString::fromUtf8("DebugBtn"));
        DebugBtn->setGeometry(QRect(70, 70, 89, 25));
        DebugBtn_2 = new QPushButton(centralwidget);
        DebugBtn_2->setObjectName(QString::fromUtf8("DebugBtn_2"));
        DebugBtn_2->setGeometry(QRect(70, 120, 89, 25));
        DebugBtn_3 = new QPushButton(centralwidget);
        DebugBtn_3->setObjectName(QString::fromUtf8("DebugBtn_3"));
        DebugBtn_3->setGeometry(QRect(70, 170, 89, 25));
        DebugBtn_4 = new QPushButton(centralwidget);
        DebugBtn_4->setObjectName(QString::fromUtf8("DebugBtn_4"));
        DebugBtn_4->setGeometry(QRect(70, 220, 89, 25));
        DebugBtn_5 = new QPushButton(centralwidget);
        DebugBtn_5->setObjectName(QString::fromUtf8("DebugBtn_5"));
        DebugBtn_5->setGeometry(QRect(70, 270, 89, 25));
        DebugBtn_6 = new QPushButton(centralwidget);
        DebugBtn_6->setObjectName(QString::fromUtf8("DebugBtn_6"));
        DebugBtn_6->setGeometry(QRect(70, 320, 89, 25));
        DebugBtn_7 = new QPushButton(centralwidget);
        DebugBtn_7->setObjectName(QString::fromUtf8("DebugBtn_7"));
        DebugBtn_7->setGeometry(QRect(70, 370, 89, 25));
        DebugBtn_8 = new QPushButton(centralwidget);
        DebugBtn_8->setObjectName(QString::fromUtf8("DebugBtn_8"));
        DebugBtn_8->setGeometry(QRect(70, 410, 89, 25));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(210, 50, 541, 511));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        DebugBtn->setText(QApplication::translate("MainWindow", "debug", nullptr));
        DebugBtn_2->setText(QApplication::translate("MainWindow", "debug2", nullptr));
        DebugBtn_3->setText(QApplication::translate("MainWindow", "debug3", nullptr));
        DebugBtn_4->setText(QApplication::translate("MainWindow", "debug4", nullptr));
        DebugBtn_5->setText(QApplication::translate("MainWindow", "debug5", nullptr));
        DebugBtn_6->setText(QApplication::translate("MainWindow", "debug6", nullptr));
        DebugBtn_7->setText(QApplication::translate("MainWindow", "debug7", nullptr));
        DebugBtn_8->setText(QApplication::translate("MainWindow", "debug8", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
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
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        DebugBtn = new QPushButton(centralwidget);
        DebugBtn->setObjectName("DebugBtn");
        DebugBtn->setGeometry(QRect(70, 70, 89, 25));
        DebugBtn_2 = new QPushButton(centralwidget);
        DebugBtn_2->setObjectName("DebugBtn_2");
        DebugBtn_2->setGeometry(QRect(70, 120, 89, 25));
        DebugBtn_3 = new QPushButton(centralwidget);
        DebugBtn_3->setObjectName("DebugBtn_3");
        DebugBtn_3->setGeometry(QRect(70, 170, 89, 25));
        DebugBtn_4 = new QPushButton(centralwidget);
        DebugBtn_4->setObjectName("DebugBtn_4");
        DebugBtn_4->setGeometry(QRect(70, 220, 89, 25));
        DebugBtn_5 = new QPushButton(centralwidget);
        DebugBtn_5->setObjectName("DebugBtn_5");
        DebugBtn_5->setGeometry(QRect(70, 270, 89, 25));
        DebugBtn_6 = new QPushButton(centralwidget);
        DebugBtn_6->setObjectName("DebugBtn_6");
        DebugBtn_6->setGeometry(QRect(70, 320, 89, 25));
        DebugBtn_7 = new QPushButton(centralwidget);
        DebugBtn_7->setObjectName("DebugBtn_7");
        DebugBtn_7->setGeometry(QRect(70, 370, 89, 25));
        DebugBtn_8 = new QPushButton(centralwidget);
        DebugBtn_8->setObjectName("DebugBtn_8");
        DebugBtn_8->setGeometry(QRect(70, 410, 89, 25));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(210, 50, 541, 511));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        DebugBtn->setText(QCoreApplication::translate("MainWindow", "debug", nullptr));
        DebugBtn_2->setText(QCoreApplication::translate("MainWindow", "debug2", nullptr));
        DebugBtn_3->setText(QCoreApplication::translate("MainWindow", "debug3", nullptr));
        DebugBtn_4->setText(QCoreApplication::translate("MainWindow", "debug4", nullptr));
        DebugBtn_5->setText(QCoreApplication::translate("MainWindow", "debug5", nullptr));
        DebugBtn_6->setText(QCoreApplication::translate("MainWindow", "debug6", nullptr));
        DebugBtn_7->setText(QCoreApplication::translate("MainWindow", "debug7", nullptr));
        DebugBtn_8->setText(QCoreApplication::translate("MainWindow", "debug8", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

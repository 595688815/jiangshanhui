/********************************************************************************
** Form generated from reading UI file 'uidisplay.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UIDISPLAY_H
#define UI_UIDISPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UIdisplay
{
public:

    void setupUi(QWidget *UIdisplay)
    {
        if (UIdisplay->objectName().isEmpty())
            UIdisplay->setObjectName("UIdisplay");
        UIdisplay->resize(1069, 573);

        retranslateUi(UIdisplay);

        QMetaObject::connectSlotsByName(UIdisplay);
    } // setupUi

    void retranslateUi(QWidget *UIdisplay)
    {
        UIdisplay->setWindowTitle(QCoreApplication::translate("UIdisplay", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UIdisplay: public Ui_UIdisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UIDISPLAY_H

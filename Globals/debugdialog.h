#ifndef DEBUGDIALOG_H
#define DEBUGDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include "globals.h"

namespace Ui {
class DebugDialog;
}

class DebugDialog : public QWidget
{
    Q_OBJECT

public:
    explicit DebugDialog(QWidget *parent = nullptr);
    ~DebugDialog();

private slots:
    void on_pushButton_clicked();

    void on_RefreshBtn_clicked();

private:
    Ui::DebugDialog *ui;

    QList<QPushButton*> m_btn_list;
    QList<QLineEdit*> m_line_list;
    QTimer *timer;
};

#endif // DEBUGDIALOG_H

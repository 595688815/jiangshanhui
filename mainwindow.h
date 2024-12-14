#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "systemsql.h"
#include "jsonfile.h"
#include "systembaseuser.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_DebugBtn_clicked();

    void on_DebugBtn_2_clicked();

    void on_DebugBtn_3_clicked();

    void on_DebugBtn_4_clicked();

    void on_DebugBtn_5_clicked();

    void on_DebugBtn_6_clicked();

    void on_DebugBtn_7_clicked();

    void on_DebugBtn_8_clicked();

private:
    Ui::MainWindow *ui;
    JsonFile* m_jsonfile;
};

#endif // MAINWINDOW_H

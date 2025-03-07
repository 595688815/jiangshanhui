#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Mysql/systemsql.h"
#include "Filesystem/jsonfile.h"
#include "Datasystem/serialport.h"
#include "DPLCExt/dplcserver.h"
#include "Globals/debugdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static void test();

private slots:
    void on_DebugBtn_clicked();

    void on_DebugBtn_2_clicked();

    void on_DebugBtn_3_clicked();

    void on_DebugBtn_4_clicked();

    void on_DebugBtn_5_clicked();

    void on_DebugBtn_6_clicked();

    void on_DebugBtn_7_clicked();

    void on_DebugBtn_8_clicked();

    void Rcv_Msg();
private:
    Ui::MainWindow *ui;
    SerialPort *m_serialport;
    std::thread *t;
    DebugDialog *m_debugdlg;
signals:
    void Exit_Soft();
};

#endif // MAINWINDOW_H

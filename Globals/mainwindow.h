#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Mysql/systemsql.h"
#include "Filesystem/jsonfile.h"
#include "Datasystem/serialport.h"

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

    void Rcv_Msg();
private:
    Ui::MainWindow *ui;
    JsonFile* m_jsonfile;
    SerialPort *m_serialport;
};

#endif // MAINWINDOW_H

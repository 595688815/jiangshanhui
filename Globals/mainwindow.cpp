#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QCoreApplication>
#include <ctime>
#include <iomanip>
#include <QDateTime>
#include <sstream>
#include <thread>
#include <QTimer>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Globals::getInstance()->GetSysTime();
    // m_serialport=new SerialPort("ttyUSB0");
    // connect(m_serialport->m_serialport,&QSerialPort::readyRead,this,&MainWindow::Rcv_Msg);
    // QStringList list=m_serialport->GetAllComList();
    // for(QString item:list)
    //     ui->lineEdit->setText(ui->lineEdit->text()+item);
    // if(m_serialport->OpenPort())
    //     qDebug()<<"Open suc";
    // else
    //     qDebug()<<"Open fail";
}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::test()
{
    qDebug()<<"123";
}

void MainWindow::on_DebugBtn_clicked()
{
    m_debugdlg=new DebugDialog;
    m_debugdlg->show();
    //ui->textEdit->setText(msg);
    //JsonFile::getInstance()->VarToJsonFile();
    //std::thread t(test);
    //MainWindow::t.join();
    //t.join();
    //char* ch1=new char('0');
    // uint16_t crc = Globals::getInstance()->getCRC(ch,5);

    // QByteArray str;//=Project_Changhui_SP::getInstance()->AskMai8DynamicsData();
    // m_serialport->m_serialport->write(str);
}

void MainWindow::on_DebugBtn_2_clicked()
{
    qDebug() << QSqlDatabase::drivers();
    //SystemSql::getInstance()->ConnectToMySQL("SystemData");
    //unsigned char a = Globals::getInstance()->m_var_value_array[0];
    //a++;
    // uint8_t ch[4];
    // float f=3.14f;
    // memcpy(ch,&f,sizeof(f));
    // qDebug()<<ch[0];
    // qDebug()<<ch[1];
    // qDebug()<<ch[2];
    // qDebug()<<ch[3];
    // float f1=*((float*)ch);
    // qDebug()<<f1;
}

void MainWindow::on_DebugBtn_3_clicked()
{
    QStringList list;
    list<<"name"<<"start"<<"fresh";
    SystemSql::getInstance()->CreateTable("VCC",list);
}

void MainWindow::on_DebugBtn_4_clicked()
{

}

void MainWindow::on_DebugBtn_5_clicked()
{

}

void MainWindow::on_DebugBtn_6_clicked()
{
    QString filePath = "NodeConfigTable.json";
    if (JsonFile::getInstance()->ReadJsonFile(filePath))
    {

    }
    else
    {

    }
    DPLCServer::getInstance()->RefreshDPLCConnect();
}

void MainWindow::on_DebugBtn_7_clicked()
{
    QString filePath = "NodeConfigTable1.json";
    if (JsonFile::getInstance()->ReadJsonFile(filePath))
    {

    }
    else
    {

    }
    DPLCServer::getInstance()->RefreshDPLCConnect();
}

void MainWindow::on_DebugBtn_8_clicked()
{
    //清空DPLC模块
    // QList<Module> *p_modelist=Globals::getInstance()->GetStationList();
    // p_modelist->clear();
    QProcess process;
    process.start("ps -o rss= -p " + QString::number(QCoreApplication::applicationPid()));
    process.waitForFinished();
    QString output = process.readAllStandardOutput();
    qDebug() << "Memory usage (in KB):" << output.trimmed();
}

void MainWindow::Rcv_Msg()
{

}


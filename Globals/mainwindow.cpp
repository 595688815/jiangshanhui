#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <ctime>
#include <iomanip>
#include <QDateTime>

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

void MainWindow::on_DebugBtn_clicked()
{
    // QByteArray str=Project_Changhui_SP::getInstance()->AskMai8DynamicsData();
    // m_serialport->m_serialport->write(str);
}

void MainWindow::on_DebugBtn_2_clicked()
{
    SystemSql::getInstance()->ConnectToMySQL("ChangHuiSql");
    // QString lstr=ui->lineEdit->text();
    // QStringList list=ui->lineEdit_2->text().split(',');
    // systemsql::getInstance()->InsertData(lstr,list);
    // QByteArray msg="";
    // msg.append(0x01);   //地址
    // msg.append(0x03);   //读标识
    // msg.append((char)0x00);
    // msg.append((char)0x00);
    // msg.append((char)0x00);
    // msg.append(0x30);
    // msg.append(0x45);
    // msg.append(0xDE);
    // if (m_serialport->m_serialport != nullptr)
    // {
    //     if(!m_serialport->m_serialport->write(msg))
    //         qDebug()<<"Send Fail";
    // }
}

void MainWindow::on_DebugBtn_3_clicked()
{
    QString lstr=ui->lineEdit->text();
    QStringList list=ui->lineEdit_2->text().split(',');
    SystemSql::getInstance()->CreateTable(lstr,list);
}

void MainWindow::on_DebugBtn_4_clicked()
{
    QString lstr=ui->lineEdit->text();
    QString num=ui->lineEdit_2->text();
    SystemSql::getInstance()->DeleteData(lstr,num);
}

void MainWindow::on_DebugBtn_5_clicked()
{
    SystemSql::getInstance()->DeleteTable(ui->lineEdit->text());
}

void MainWindow::on_DebugBtn_6_clicked()
{
    QString filePath = "/mnt/hgfs/Share/zutai1.json";
    if (m_jsonfile->ReadJsonFile(filePath))
    {

    }
    else
    {

    }
}

void MainWindow::on_DebugBtn_7_clicked()
{

}

void MainWindow::on_DebugBtn_8_clicked()
{

}

void MainWindow::Rcv_Msg()
{
    QByteArray msg=m_serialport->m_serialport->readAll();
    QString str=msg.toHex();
    ui->lineEdit_2->setText(ui->lineEdit_2->text() + str);
}


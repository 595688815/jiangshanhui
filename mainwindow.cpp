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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_DebugBtn_clicked()
{
    //systemsql::getInstance()->ConnectToMySQL();
    // qDebug()<<ui->lineEdit->text();
    // m_class_port->ConfigPort(ui->lineEdit->text(),m_class_port->GetPortRate(),m_class_port->GetPortParity(),m_class_port->GetPortStop(),m_class_port->GetPortData());
    // if(m_class_port->OpenPort())
    //     qDebug()<<"suc";
    // else
    //     qDebug()<<"fail";
}

void MainWindow::on_DebugBtn_2_clicked()
{
    // QString lstr=ui->lineEdit->text();
    // QStringList list=ui->lineEdit_2->text().split(',');
    // systemsql::getInstance()->InsertData(lstr,list);
    // if (m_class_port != nullptr)
    // {
    //     if(!m_class_port->SendMsg(ui->lineEdit->text().toLocal8Bit()))
    //         qDebug()<<"Send Fail";
    // }
}

void MainWindow::on_DebugBtn_3_clicked()
{
    QString lstr=ui->lineEdit->text();
    QStringList list=ui->lineEdit_2->text().split(',');
    systemsql::getInstance()->CreateTable(lstr,list);
}

void MainWindow::on_DebugBtn_4_clicked()
{
    QString lstr=ui->lineEdit->text();
    QString num=ui->lineEdit_2->text();
    systemsql::getInstance()->DeleteData(lstr,num);
}

void MainWindow::on_DebugBtn_5_clicked()
{
    systemsql::getInstance()->DeleteTable(ui->lineEdit->text());
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

void MainWindow::Rcv_Msg(QByteArray msg)
{
    ui->lineEdit_2->setText(ui->lineEdit_2->text() + msg);
}


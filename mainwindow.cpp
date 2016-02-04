#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    createCOMPortList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createCOMPortList()
{
    ui->comboBoxPort->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->comboBoxPort->addItem(info.portName());
    }
}

void MainWindow::on_pushButtonRead_clicked()
{

}

void MainWindow::on_pushButtonWrite_clicked()
{

}

void MainWindow::on_pushButtonStartStop_clicked()
{

}

void MainWindow::on_pushButtonUpdPortList_clicked()
{
    createCOMPortList();
}

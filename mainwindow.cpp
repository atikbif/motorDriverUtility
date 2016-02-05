#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSerialPort/QSerialPortInfo>
#include "driversettings.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), startRpm(false),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setLimits();

    scManager = new ScanManager();
    scManager->updateCom(ui->comboBoxPort->currentText());
    connect(scManager, &ScanManager::rpmUpdate, this, &MainWindow::rpmUpdate);
    connect(scManager, &ScanManager::readFinished, this, &MainWindow::readFinished);
    connect(scManager, &ScanManager::writeFinished, this, &MainWindow::writeFinished);
    connect(scManager, &ScanManager::errorMessage, this, &MainWindow::errorMessage);

    createCOMPortList();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scManager;
}

void MainWindow::createCOMPortList()
{
    ui->comboBoxPort->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        ui->comboBoxPort->addItem(info.portName());
    }
}

void MainWindow::setLimits()
{
    ui->spinBoxPolus->setMinimum(DriverSettings::getPolarPairsMin());
    ui->spinBoxPolus->setMaximum(DriverSettings::getPolarPairsMax());
    ui->spinBoxPolus->setToolTip("min:" + QString::number(ui->spinBoxPolus->minimum()) +
                                 " max:" + QString::number(ui->spinBoxPolus->maximum()));

    ui->spinBoxRpmSet->setMinimum(DriverSettings::getRpmGoalMin());
    ui->spinBoxRpmSet->setMaximum(DriverSettings::getRpmGoalMax());
    ui->spinBoxRpmSet->setToolTip("(об/минуту) 0-ручной режим, min:300 max:" + QString::number(ui->spinBoxRpmSet->maximum()));

    ui->spinBoxStartPwm->setMinimum(DriverSettings::getStartPwmMin());
    ui->spinBoxStartPwm->setMaximum(DriverSettings::getStartPwmMax());
    ui->spinBoxStartPwm->setToolTip("min:" + QString::number(ui->spinBoxStartPwm->minimum()) +
                                    " max:" + QString::number(ui->spinBoxStartPwm->maximum()));

    ui->spinBoxStartRpm->setMinimum(DriverSettings::getStartRpmMin());
    ui->spinBoxStartRpm->setMaximum(DriverSettings::getStartRpmMax());
    ui->spinBoxStartRpm->setToolTip("min:" + QString::number(ui->spinBoxStartRpm->minimum()) +
                                    " max:" + QString::number(ui->spinBoxStartRpm->maximum()));

    ui->spinBoxStartSpeed->setMinimum(DriverSettings::getRpmUpSpeedMin());
    ui->spinBoxStartSpeed->setMaximum(DriverSettings::getRpmUpSpeedMax());
    ui->spinBoxStartSpeed->setToolTip("(об/секунду) min:" + QString::number(ui->spinBoxStartSpeed->minimum()) +
                                      " max:" + QString::number(ui->spinBoxStartSpeed->maximum()));
}

void MainWindow::on_pushButtonRead_clicked()
{
    scManager->readSettings();
}

void MainWindow::on_pushButtonWrite_clicked()
{
    DriverSettings settings;
    settings.setPolarPairs(ui->spinBoxPolus->value());
    settings.setRpmGoal(ui->spinBoxRpmSet->value());
    settings.setRpmUpSpeed(ui->spinBoxStartSpeed->value());
    settings.setStartPwm(ui->spinBoxStartPwm->value());
    settings.setStartRpm(ui->spinBoxStartRpm->value());
    scManager->writeSettings(settings);
}

void MainWindow::on_pushButtonStartStop_clicked()
{
    if(startRpm==false) {
        startRpm = true;
        ui->pushButtonStartStop->setText("Стоп");
        scManager->enableCurrentRpmRead();
    }else {
        startRpm = false;
        ui->pushButtonStartStop->setText("Старт");
        scManager->disableCurrentRpmRead();
    }
}

void MainWindow::on_pushButtonUpdPortList_clicked()
{
    createCOMPortList();
    scManager->updateCom(ui->comboBoxPort->currentText());
}

void MainWindow::on_comboBoxPort_currentIndexChanged(const QString &arg1)
{
    scManager->updateCom(arg1);
}

void MainWindow::rpmUpdate(int rpmValue)
{
    ui->lcdNumberCurRpm->display(rpmValue);
}

void MainWindow::writeFinished(const QString &message)
{
    ui->statusBar->showMessage(message,2000);
}

void MainWindow::readFinished(const DriverSettings &conf, const QString &message)
{
    ui->spinBoxPolus->setValue(conf.getPolarPairs());
    ui->spinBoxRpmSet->setValue(conf.getRpmGoal());
    ui->spinBoxStartSpeed->setValue(conf.getRpmUpSpeed());
    ui->spinBoxStartPwm->setValue(conf.getStartPwm());
    ui->spinBoxStartRpm->setValue(conf.getStartRpm());
    ui->statusBar->showMessage(message,2000);
}

void MainWindow::errorMessage(const QString &message)
{
    ui->statusBar->showMessage(message,2000);
}

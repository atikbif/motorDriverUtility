#include "scanmanager.h"

ScanManager::ScanManager(QObject *parent) : QObject(parent), portName("COM1")
{
    scan = new Scanner(portName);
    scan->moveToThread(&scanThread);
    connect(&scanThread, &QThread::finished, scan, &QObject::deleteLater);
    connect(this, &ScanManager::operate, scan, &Scanner::startScan);
    connect(scan, &Scanner::readFinished, this, &ScanManager::readFinished);
    connect(scan, &Scanner::writeFinished, this, &ScanManager::writeFinished);
    connect(scan, &Scanner::rpmUpdate, this, &ScanManager::rpmUpdate);
    connect(scan, &Scanner::errorMessage, this, &ScanManager::errorMessage);
    scanThread.start();
    emit operate();
}

ScanManager::~ScanManager()
{
    scan->stopScan();
    scanThread.quit();
    scanThread.wait();
}

void ScanManager::updateCom(const QString &pName)
{
    scan->updateCom(pName);
}

void ScanManager::readSettings()
{
    scan->readSettings();
}

void ScanManager::writeSettings(const DriverSettings &conf)
{
    scan->writeSettings(conf);
}

void ScanManager::enableCurrentRpmRead()
{
    scan->enableCurrentRpmRead();
}

void ScanManager::disableCurrentRpmRead()
{
    scan->disableCurrentRpmRead();
}

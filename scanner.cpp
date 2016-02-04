#include "scanner.h"
#include <QMutexLocker>
#include <QThread>

Scanner::Scanner(const QString &pName, QObject *parent) : QObject(parent), portName(pName), drConf(DriverSettings()),
    curRpmRead(false), stopFlag(false), rdFlag(false), wrFlag(false)
{

}

void Scanner::readSettings()
{
    QMutexLocker locker(&mutex);
    rdFlag = true;
}

void Scanner::writeSettings(const DriverSettings &conf)
{
    QMutexLocker locker(&mutex);
    drConf = conf;
    wrFlag = true;
}

void Scanner::startScan()
{
    // чтение и запись данных при необходимости
    for(;;) {
        mutex.lock();
        if(stopFlag) {mutex.unlock();break;}
        mutex.unlock();
        QThread::currentThread()->msleep(100);
    }
}

void Scanner::stopScan()
{
    QMutexLocker locker(&mutex);
    stopFlag = true;
}

void Scanner::enableCurrentRpmRead()
{
    QMutexLocker locker(&mutex);
    curRpmRead = true;
}

void Scanner::disableCurrentRpmRead()
{
    QMutexLocker locker(&mutex);
    curRpmRead = false;
}

void Scanner::updateCom(const QString &pName)
{
    QMutexLocker locker(&mutex);
    portName = pName;
}

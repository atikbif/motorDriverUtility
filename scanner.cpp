#include "scanner.h"
#include <QMutexLocker>
#include <QThread>
#include "modbusrequest.h"

bool Scanner::openPort(const QString &pName, QSerialPort &port)
{
    port.setPortName(pName);
    port.setBaudRate(QSerialPort::Baud115200);
    port.setDataBits(QSerialPort::Data8);
    port.setParity(QSerialPort::NoParity);
    port.setStopBits(QSerialPort::OneStop);
    port.setFlowControl(QSerialPort::NoFlowControl);
    if(port.open(QSerialPort::ReadWrite)) return true;
    return false;
}

void Scanner::writeAndRead(QByteArray &data, QSerialPort &port)
{
    port.write(data);
    port.waitForBytesWritten(100);
    data.clear();
    if(port.waitForReadyRead(100)){
        int cnt=0;
        data+=port.readAll();
        while(port.waitForReadyRead(10)) {
            data+=port.readAll();
            cnt++;if(cnt>=500) break;
        }
    }
}

Scanner::Scanner(const QString &pName, QObject *parent) : QObject(parent), portName(pName), drConf(DriverSettings()),
    curRpmRead(false), stopFlag(false), rdFlag(false), wrFlag(false)
{
    qRegisterMetaType<DriverSettings>("DriverSettings");
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

        mutex.lock();
        if(rdFlag) {
            rdFlag = false;
            mutex.unlock();

            QSerialPort port;
            if(openPort(portName, port)) {
                QByteArray data;
                data = ModbusRequest::getReadRequest(0x01,0x01,5);
                writeAndRead(data, port);
                if(!data.isEmpty()) {
                    QVector<quint16> res = ModbusRequest::getDataFromReadAnswer(data);
                    if(res.count()) {
                        DriverSettings settings;
                        // 0 -current rpm
                        settings.setPolarPairs(res.at(0));
                        settings.setStartPwm(res.at(1));
                        settings.setStartRpm(res.at(2));
                        settings.setRpmUpSpeed(res.at(3));
                        settings.setRpmGoal(res.at(4));
                        emit readFinished(settings,"Настройки успешно прочитаны");
                    }else emit errorMessage("Некорректный ответ");
                }else emit errorMessage("Контроллер не отвечает");
                port.close();
            }else emit errorMessage("Ошибка открытия порта");


        }else mutex.unlock();

        mutex.lock();
        if(wrFlag) {
            wrFlag = false;
            mutex.unlock();
            QSerialPort port;
            if(openPort(portName, port)) {
                QVector<quint16> regs;
                regs.append(drConf.getPolarPairs());
                regs.append(drConf.getStartPwm());
                regs.append(drConf.getStartRpm());
                regs.append(drConf.getRpmUpSpeed());
                regs.append(drConf.getRpmGoal());
                QByteArray data;
                data = ModbusRequest::getWriteRequest(0x01,0x01,5,regs);
                writeAndRead(data, port);
                if(!data.isEmpty()) {
                    emit writeFinished("Настройки успешно записаны");
                }else emit errorMessage("Контроллер не отвечает");
                port.close();
            }else emit errorMessage("Ошибка открытия порта");

        }else mutex.unlock();

        mutex.lock();
        if(curRpmRead) {
            mutex.unlock();
            // чтение текущих оборотов
            QSerialPort port;
            if(openPort(portName, port)) {
                QByteArray data;
                data = ModbusRequest::getReadRequest(0x01,0x00,1);
                writeAndRead(data, port);
                if(!data.isEmpty()) {
                    QVector<quint16> res = ModbusRequest::getDataFromReadAnswer(data);
                    if(res.count()) {
                        emit rpmUpdate(res.at(0));
                    }else emit errorMessage("Некорректный ответ");
                }else emit errorMessage("Контроллер не отвечает");
                port.close();
            }else emit errorMessage("Ошибка открытия порта");
        }else mutex.unlock();
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

#ifndef SCANNER_H
#define SCANNER_H

#include <QObject>
#include "driversettings.h"
#include <QString>
#include <QMutex>

class Scanner : public QObject
{
    Q_OBJECT
    QString portName;
    DriverSettings drConf;
    bool curRpmRead;
    bool stopFlag;
    bool rdFlag;
    bool wrFlag;
    QMutex mutex;

public:
    explicit Scanner(const QString &pName, QObject *parent = 0);
    void readSettings(void);
    void writeSettings(const DriverSettings &conf);
    void stopScan(void);
    void enableCurrentRpmRead(void);
    void disableCurrentRpmRead(void);
    void updateCom(const QString &pName);

signals:
    void rpmUpdate(int rpmValue);
    void writeFinished(const QString &message);
    void readFinished(const DriverSettings &conf, const QString &message);

public slots:
    void startScan(void);

};

#endif // SCANNER_H

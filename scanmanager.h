#ifndef SCANMANAGER_H
#define SCANMANAGER_H

#include <QObject>
#include <QThread>

#include "scanner.h"
#include <QString>

class ScanManager : public QObject
{
    Q_OBJECT
    Scanner *scan;
    QThread scanThread;
    QString portName;
public:
    explicit ScanManager(QObject *parent = 0);
    ~ScanManager();
    void updateCom(const QString &pName);
    void readSettings(void);
    void writeSettings(const DriverSettings &conf);
    void enableCurrentRpmRead(void);
    void disableCurrentRpmRead(void);


signals:
    void operate(void);
    void rpmUpdate(int rpmValue);
    void writeFinished(const QString &message);
    void readFinished(const DriverSettings &conf, const QString &message);
public slots:
};

#endif // SCANMANAGER_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "scanmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    ScanManager *scManager;
    bool startRpm;
    void createCOMPortList(void);
    void setLimits(void);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonRead_clicked();

    void on_pushButtonWrite_clicked();

    void on_pushButtonStartStop_clicked();

    void on_pushButtonUpdPortList_clicked();

    void on_comboBoxPort_currentIndexChanged(const QString &arg1);

    void rpmUpdate(int rpmValue);
    void writeFinished(const QString &message);
    void readFinished(const DriverSettings &conf, const QString &message);
    void errorMessage(const QString &message);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

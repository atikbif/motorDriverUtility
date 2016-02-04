#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    void createCOMPortList(void);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButtonRead_clicked();

    void on_pushButtonWrite_clicked();

    void on_pushButtonStartStop_clicked();

    void on_pushButtonUpdPortList_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

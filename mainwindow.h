#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void on_comboBoxPort_currentIndexChanged(int index);
    void on_pushButtonEnviar_clicked();
    void on_pushButtonConectar_clicked();
    void on_Port_rx();

    void on_LedRojoPushButton_clicked();

    void on_LedVerdePushButton_clicked();

    void on_LedAzulPushButton_clicked();

private:
    QString Portname;
    //QextSerialPort *Port;
    QSerialPort *Port;
    void EnumerarPuertos();
};

#endif // MAINWINDOW_H

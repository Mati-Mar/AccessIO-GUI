#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSqlDatabase>
#include <QMainWindow>
#include <QSerialPortInfo>

#include <postgresqlconnector.h>

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
    void on_pushButtonConectar_clicked();
    void on_Port_rx();
    void on_sinConexionPushButton_clicked();

private:
    QString Portname;
    //QextSerialPort *Port;
    void EnumerarPuertos();
    PostgreSQLConnector *SQLConnector;
    void abrirFrontpage(bool isUartConnectedFlag);
};

#endif // MAINWINDOW_H

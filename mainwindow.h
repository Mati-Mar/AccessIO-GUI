#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSqlDatabase>
#include <QMainWindow>
#include <QSerialPort>
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
    void on_pushButtonEnviar_clicked();
    void on_pushButtonConectar_clicked();
    void on_Port_rx();

    void on_pushButton_clicked();

    void on_testingPushButton_clicked();

private:
    QString Portname;
    //QextSerialPort *Port;
    QSerialPort *Port;
    void EnumerarPuertos();
    PostgreSQLConnector *SQLConnector;
};

#endif // MAINWINDOW_H

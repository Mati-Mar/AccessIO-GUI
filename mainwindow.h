#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>

#include "frontpage.h"

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
    void on_sinConexionPushButton_clicked();
private:
    QString Portname;
    FrontPage * frontPage;
    QByteArray RcArr;

    void EnumerarPuertos();
    void abrirFrontpage(bool isUartConnectedFlag);
};

#endif // MAINWINDOW_H

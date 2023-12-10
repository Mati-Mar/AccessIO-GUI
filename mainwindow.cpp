#include "mainwindow.h"
#include "frontpage.h"
#include "ui_mainwindow.h"

#include <QByteArray>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("AccessIO");
    this->setFixedSize(540,100);
    Portname = "";
    EnumerarPuertos();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::EnumerarPuertos()
{
    ui->comboBoxPort->clear();

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    for (int i = 0; i < ports.size(); i++)
    {
        ui->comboBoxPort->addItem(ports.at(i).portName(), ports.at(i).portName());
    }
}

void MainWindow::abrirFrontpage(bool isUartConnectedFlag) {
    FrontPage *frontPage;
    if (isUartConnectedFlag)
        frontPage = new FrontPage(nullptr, Portname); //Modo UART
    else
        frontPage = new FrontPage(nullptr, ""); //Modo SIN CONEXION
    frontPage->setWindowTitle("AccessIO");
    frontPage->show();
    this->hide();

}

void MainWindow::on_pushButtonConectar_clicked()
{
    (Portname != "") ? abrirFrontpage(true) : abrirFrontpage(false);
}

void MainWindow::on_comboBoxPort_currentIndexChanged(int index)
{
    Portname = ui->comboBoxPort->itemData(index).toString();    //recupero la data del item de indice index
}

void MainWindow::on_sinConexionPushButton_clicked()
{
    abrirFrontpage(false);
}

#include "mainwindow.h"
#include "frontpage.h"
#include "ui_mainwindow.h"
#include "postgresqlconnector.h"

#include <QMessageBox>
#include <QByteArray>
#include <QSqlDatabase>
#include <QSqlQuery>

//ELIMINAR LUEGO
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("AccessIO");

    Port = NULL; //indica que el objeto puerto no esta creado
    Portname = "";
    EnumerarPuertos();
    SQLConnector = new PostgreSQLConnector
        ("localhost","AccessIO","postgres","accessio","root");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete Port;
    delete SQLConnector;
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

void MainWindow::on_pushButtonConectar_clicked()
{
    if (!Port)
    {
        Port = new QSerialPort(Portname);
        Port->setBaudRate(QSerialPort::Baud9600);
        Port->setFlowControl(QSerialPort::NoFlowControl);
        Port->setParity(QSerialPort::NoParity);
        Port->setDataBits(QSerialPort::Data8);
        Port->setStopBits(QSerialPort::OneStop);
        if(!Port->open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(this,"Error","No se puede abrir el puerto "+Port->portName());
            delete Port;
            Port = NULL;
        }
        else
        {
            ui->pushButtonConectar->setText("Desconectar");
            connect(Port,SIGNAL(readyRead()),this,SLOT(on_Port_rx()));
            //TODO: CON EL LPC CONECTADO CODEAR ACA
        }
    }
    else
    {
        delete Port;
        Port = NULL;
        ui->pushButtonConectar->setText("Conectar");
    }
}

void MainWindow::on_pushButtonEnviar_clicked()
{
    if(Port)
    {
        QByteArray aux;
        aux.append(ui->plainTextEditTX->toPlainText());

        Port->write(aux);
        ui->plainTextEditTX->clear();
    }
    else
    {
        QMessageBox::critical(this,"Error",QString::fromLatin1("No hay ningún puerto abierto"));
    }
}

void MainWindow::on_Port_rx()
{
    QByteArray aux;
    aux.resize(Port->bytesAvailable());
    Port->read(aux.data(),aux.size());
    ui->plainTextEditRX->appendPlainText(aux);
}

void MainWindow::on_comboBoxPort_currentIndexChanged(int index)
{
    Portname = ui->comboBoxPort->itemData(index).toString();    //recupero la data del item de indice index
}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}


void MainWindow::on_testingPushButton_clicked()
{
    QSqlQuery query;
    QString resultado;
//    if (SQLConnector->abrirConexionBD())
//    {
//        query = SQLConnector->ejecutarQuery("SELECT nombre FROM " + SQLConnector->getSchema() + ".usuarios");
//        while(query.next()){
//            resultado += query.value(0).toString() + "\n";
//        }
//        ui->testLabel->setText(resultado);
//        SQLConnector->cerrarConexionBD();
        FrontPage *frontPage = new FrontPage(nullptr, Portname);
        frontPage->setWindowTitle("AccessIO");
        frontPage->show();
        this->hide();
//    }
//    else
//    {
//        qDebug() << SQLConnector->getError();
//        QMessageBox::critical(this,"Error",QString::fromLatin1("Error con la conexión a la base de datos"));
//    }

}

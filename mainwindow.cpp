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
    this->setFixedSize(540,100);

    //Port = NULL; //indica que el objeto puerto no esta creado
    Portname = "";
    EnumerarPuertos();
    SQLConnector = new PostgreSQLConnector
        ("localhost","AccessIO","postgres","accessio","root");
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::abrirFrontpage(bool isUartConnectedFlag) {

    if (isUartConnectedFlag)
    {
        //Modo UART
        FrontPage *frontPage = new FrontPage(nullptr, Portname);
        frontPage->setWindowTitle("AccessIO");
        frontPage->show();
        this->hide();
    } else {
        //Modo SIN CONEXION
        FrontPage* frontPage = new FrontPage(nullptr, "");
        frontPage->setWindowTitle("AccessIO");
        frontPage->show();
        this->hide();
    }

}

//Hay que corregir este método
void MainWindow::on_pushButtonConectar_clicked()
{
    //Portname = ui->comboBoxPort->itemData(index).toString();    //recupero la data del item de indice index
    if (Portname != "")
    {
        abrirFrontpage(true);
        //Quiero deshabilitar el botón
        //ui->pushButtonConectar->setText("Desconectar");


        /*if(!Port->open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(this,"Error","No se puede abrir el puerto "+Port->portName());
        }
        else
        {

            connect(Port,SIGNAL(readyRead()),this,SLOT(on_Port_rx()));

            abrirFrontpage(true);
        }
        */
    }
    else
    {
        abrirFrontpage(false);
        //Quiero deshabilitar el botón
        //ui->pushButtonConectar->toggle();
    }
}




/*
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
*/


void MainWindow::on_Port_rx()
{
//    QByteArray aux;
//    aux.resize(Port->bytesAvailable());
//    Port->read(aux.data(),aux.size());
//    ui->plainTextEditRX->appendPlainText(aux);

}

void MainWindow::on_comboBoxPort_currentIndexChanged(int index)
{
    Portname = ui->comboBoxPort->itemData(index).toString();    //recupero la data del item de indice index
}

void MainWindow::on_sinConexionPushButton_clicked()
{
    abrirFrontpage(false);
}

/*
void MainWindow::on_testingPushButton_clicked()
{
//    QSqlQuery query;
//    QString resultado;
//    if (SQLConnector->abrirConexionBD())
//    {
//        query = SQLConnector->ejecutarQuery("SELECT nombre FROM " + SQLConnector->getSchema() + ".usuarios");
//        while(query.next()){
//            resultado += query.value(0).toString() + "\n";
//        }
//        ui->testLabel->setText(resultado);
//        SQLConnector->cerrarConexionBD();
        abrirFrontpage(true);
//    }
//    else
//    {
//        qDebug() << SQLConnector->getError();
//        QMessageBox::critical(this,"Error",QString::fromLatin1("Error con la conexión a la base de datos"));
//    }

}
*/



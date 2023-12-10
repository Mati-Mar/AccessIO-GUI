#include "frontpage.h"
#include "ui_frontpage.h"
#include "edificiopage.h"
#include "in_outpage.h"
#include "usuariospage.h"

#include <QPixmap>
#include <QMessageBox>

FrontPage::FrontPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrontPage)
{
    //No debería iniciar por acá
    isUartConnectedFlag = false;
    setPortname("");
    initFrontpage();
}
void FrontPage::on_Port_rx()
{
    QByteArray aux;
    while(Port->bytesAvailable()) {
        Port->read(aux.data(),1);
        RcArr.append(aux.data()[0]);
        if(aux.data()[0]=='$') {
            if(RcArr[1]=='P') {
                handlePas(RcArr);
            }
            RcArr.clear();
            break;
        }
    }
}

FrontPage::FrontPage(QWidget *parent, QString portname) :
    QMainWindow(parent),
    ui(new Ui::FrontPage)
{
    this->PSQLConnector = new PostgreSQLConnector
        ("localhost","AccessIO","postgres","accessio","root");
    PSQLConnector->cerrarConexionBD();
    isUartConnectedFlag = !(portname == "");
    setPortname(portname);
    initFrontpage();
}

void FrontPage::initFrontpage() {
    ui->setupUi(this);
    QPixmap pix(":/img/accessio_logo.png");
    ui->logoLabel->setPixmap(pix.scaled(ui->logoLabel->width(),
                                        ui->logoLabel->height(),
                                        Qt::KeepAspectRatio));
    ui->logoLabel->setAlignment(Qt::AlignCenter);
    this->setFixedSize(810,310);
    initPort(getPortname());
}

void FrontPage::initPort(QString portname) {
    if (portname != "")
    {
        Port = new QSerialPort(portname);
        Port->setBaudRate(QSerialPort::Baud9600);
        Port->setFlowControl(QSerialPort::NoFlowControl);
        Port->setParity(QSerialPort::NoParity);
        Port->setDataBits(QSerialPort::Data8);
        Port->setStopBits(QSerialPort::OneStop);
        Port->open(QIODevice::ReadWrite);
        isUartConnectedFlag= true;
        connect(Port,SIGNAL(readyRead()),this,SLOT(on_Port_rx()));

    }
    else
    {
        //No eligió puerto
        QMessageBox::critical(this,"Error",QString::fromLatin1("Ingrese un puerto correcto"));
    }
}

void FrontPage::abrirEdificioPage() {
    EdificioPage *edificioPage;
    if (isUartConnectedFlag)
        edificioPage = new EdificioPage(nullptr, Port, PSQLConnector); //Modo UART
    else
        edificioPage = new EdificioPage(nullptr, nullptr, PSQLConnector); //Modo SIN CONEXION
    edificioPage->setWindowTitle("AccessIO");
    edificioPage->show();
//    this->hide();
}

void FrontPage::abrirUsuariosPage() {
    UsuariosPage *usuariosPage;
    if (isUartConnectedFlag)
        usuariosPage = new UsuariosPage(nullptr, Port, PSQLConnector); //Modo UART
    else
        usuariosPage = new UsuariosPage(nullptr, nullptr, PSQLConnector); //Modo SIN CONEXION
    usuariosPage->setWindowTitle("AccessIO");
    usuariosPage->show();
//    this->hide();
}

void FrontPage::abrirIn_OutPage() {
    In_OutPage *in_outPage;
    if (isUartConnectedFlag)
        in_outPage = new In_OutPage(nullptr, Port, PSQLConnector); //Modo UART
    else
        in_outPage = new In_OutPage(nullptr, nullptr, PSQLConnector); //Modo SIN CONEXION
    in_outPage->setWindowTitle("AccessIO");
    in_outPage->show();
//    this->hide();
}

void FrontPage::recieve(QString Rx) {
    ui->plainTextEdit->appendPlainText(Rx);
}

FrontPage::~FrontPage()
{
    if (PSQLConnector->isOpen())
        PSQLConnector->cerrarConexionBD();
    delete Port;
    delete ui;
}

void FrontPage::on_edificioPushButton_clicked()
{
    abrirEdificioPage();
}

QString FrontPage::getPortname() const
{
    return portname;
}

void FrontPage::setPortname(const QString &newPortname)
{
    portname = newPortname;
}

void FrontPage::on_usuariosPushButton_clicked()
{
    abrirUsuariosPage();
}
void FrontPage::handlePas(QByteArray RcArr){


    QString Pass;
    QString oficina;

    oficina[0] = RcArr[6];
    oficina[1] = RcArr[7];
    oficina[2] = RcArr[8];
    oficina[3] = RcArr[9];

    Pass[0] = RcArr[11];
    Pass[1] = RcArr[12];
    Pass[2] = RcArr[13];
    Pass[3] = RcArr[14];
    ui->plainTextEdit->appendPlainText("oficina: "+ oficina);

    QString secretPas = PSQLConnector->getPassword(oficina);
    ui->plainTextEdit->appendPlainText("pass: "+ Pass);
    ui->plainTextEdit->appendPlainText("secretPas: "+ secretPas);
    if(Pass == secretPas){
        //Port->write(("#pass,y,"+PqslCon->getUsernameByOficina(oficina)+"$"));

        Port->write(("#pass,y,$"));
    }
    else{
        //Port->write("#pass,N,"+PqslCon->getUsernameByOficina(oficina)+"$");
        Port->write(("#pass,N,$"));

    }
}

void FrontPage::on_inoutPushButton_clicked()
{
    abrirIn_OutPage();
}

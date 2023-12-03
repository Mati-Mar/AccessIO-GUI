#include "frontpage.h"
#include "ui_frontpage.h"
#include "edificiopage.h"
//#include "usuariospage.h"
//#include "in_outpage.h"
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

FrontPage::FrontPage(QWidget *parent, QString portname) :
    QMainWindow(parent),
    ui(new Ui::FrontPage)
{
    isUartConnectedFlag = !(portname == "");
    setPortname(portname);
    initFrontpage();
    //ui->portLabel->setText(portname);
}

void FrontPage::initFrontpage() {
    ui->setupUi(this);
    QPixmap pix(":/img/accessio_logo.jpeg");
    ui->logoLabel->setPixmap(pix.scaled(ui->logoLabel->width(),
                                        ui->logoLabel->height(),
                                        Qt::KeepAspectRatio));
    this->setFixedSize(810,310);
    if (isUartConnectedFlag)
        initPort(getPortname());
    //Si no está conectado el UART entonces es modo sin conexión
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
    }
    else
    {
        //No eligió puerto
        QMessageBox::critical(this,"Error",QString::fromLatin1("Ingrese un puerto correcto"));
    }
}

void FrontPage::abrirEdificioPage() {
    //Puede ser que acá la flag no sea necesaria porque si portname es "" entonces ya se que es sin conexión
    if (isUartConnectedFlag)
    {
        //Modo UART
        EdificioPage *edificioPage = new EdificioPage(nullptr, Port);
        edificioPage->setWindowTitle("AccessIO");
        edificioPage->show();
        this->hide();
    } else {
        //Modo SIN CONEXION
        EdificioPage* edificioPage = new EdificioPage(nullptr, nullptr);
        edificioPage->setWindowTitle("AccessIO");
        edificioPage->show();
        this->hide();
    }
}

void FrontPage::abrirUsuariosPage() {

}

void FrontPage::abrirIn_OutPage() {

}

FrontPage::~FrontPage()
{
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

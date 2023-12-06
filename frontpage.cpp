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
void FrontPage::on_Port_rx()
{
    QByteArray aux;
    while(Port->bytesAvailable()){
        Port->read(aux.data(),1);
        RcArr.append(aux.data()[0]);
        if(aux.data()[0]=='$'){

            if(RcArr[1]=='P'){
                handlePas(RcArr);
            }
            //recieve(QString(RcArr));
            /*
            PqslCon->abrirConexionBD();
            QSqlQuery * query = PqslCon->getUsername("hola");
            while (query->next()) {
                QString name = query->value(0).toString();
                ui->plainTextEdit_2->appendPlainText("name");

                ui->plainTextEdit_2->appendPlainText(name);
            }
            PqslCon->cerrarConexionBD();*/
            //Port->write("#pass,y,juan$");

            RcArr.clear();
            break;
        }
    }


}
FrontPage::FrontPage(QWidget *parent, QString portname) :
    QMainWindow(parent),
    ui(new Ui::FrontPage)
{


    PqslCon = new PostgreSQLConnector
        ("localhost","accessio","postgres","accessio","root");
    PqslCon->cerrarConexionBD();


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

void FrontPage::recieve(QString Rx) {
    ui->plainTextEdit->appendPlainText(Rx);
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

void FrontPage::on_usuariosPushButton_clicked()
{
    if(PqslCon->isOpen()){
        ui->plainTextEdit_2->appendPlainText("esta abierta como tu cola");
        PqslCon->cerrarConexionBD();
    }
    ui->plainTextEdit_2->appendPlainText("Cola");
    if(PqslCon->abrirConexionBD())
        ui->plainTextEdit->appendPlainText("true");
    else
        ui->plainTextEdit->appendPlainText("false");
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

    QString secretPas = PqslCon->getPassword(oficina);
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


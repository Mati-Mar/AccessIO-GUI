#include "frontpage.h"
#include "ui_frontpage.h"
#include "edificiopage.h"
#include "in_outpage.h"

#include <QPixmap>
#include <QMessageBox>

FrontPage::FrontPage(QWidget *parent, QString portname) :
    QMainWindow(parent),
    ui(new Ui::FrontPage)
{
    this->PSQLConnector = new PostgreSQLConnector
        ("localhost","accessio","postgres","accessio","root");
    PSQLConnector->cerrarConexionBD();
    isUartConnectedFlag = !(portname == "");
    setPortname(portname);
    initFrontpage();
}

FrontPage::~FrontPage()
{
    if (PSQLConnector->isOpen())
        PSQLConnector->cerrarConexionBD();
    delete Port;
    delete ui;
}

void FrontPage::initFrontpage() {
    ui->setupUi(this);
    QPixmap pix(":/img/accessio_logo.png");
    ui->logoLabel->setPixmap(pix.scaled(ui->logoLabel->width(),
                                        ui->logoLabel->height(),
                                        Qt::KeepAspectRatio));
    ui->logoLabel->setAlignment(Qt::AlignCenter);
    this->setFixedSize(810,310);

    ui->usuariosPushButton->setEnabled(true);
    if (isUartConnectedFlag)
        initPort(getPortname());
    else
        ui->usuariosPushButton->setEnabled(false);
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

void FrontPage::on_Port_rx()
{
    QByteArray aux;
    while(Port->bytesAvailable()) {
        Port->read(aux.data(),1);
        RcArr.append(aux.data()[0]);
        if(aux.data()[0]=='$'){

            ui->plainTextEdit_3->appendPlainText(RcArr);
            if(RcArr[1]=='P'){
                handlePas(RcArr);
            }
            if(RcArr[1]=='V'){
                ui->plainTextEdit->appendPlainText(RcArr.data());

                handleVerif(RcArr);
            }
            if(RcArr[1]=='a'){
                QByteArray dat;
                dat[0] = RcArr[5];
                dat[1] = RcArr[6];
                dat[2] = RcArr[7];
                dat[3] = RcArr[8];
                if(dat[0] != 'X')
                    usuariosPage->recieveUID(dat.toHex().data());
            }
            RcArr.clear();
            break;
        }
    }
}

void FrontPage::recieve(QString Rx) {
    ui->plainTextEdit->appendPlainText(Rx);
}

void FrontPage::on_edificioPushButton_clicked()
{
    abrirEdificioPage();
}

void FrontPage::on_usuariosPushButton_clicked()
{
    if (isUartConnectedFlag) {
        Port->write("#Caca$");
        abrirUsuariosPage();
    }
}

void FrontPage::on_inoutPushButton_clicked()
{
    abrirIn_OutPage();
}

QString FrontPage::getPortname() const
{
    return portname;
}

void FrontPage::setPortname(const QString &newPortname)
{
    portname = newPortname;
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
//#V���,A$
void FrontPage::handleVerif(QByteArray RcArr){

    QByteArray data;
    QString passNueva;
    data.append(RcArr.at(2));
    data.append(RcArr.at(3));
    data.append(RcArr.at(4));
    data.append(RcArr.at(5));
    QString enHexa = data.toHex().data();
    QString Ofi = PSQLConnector->getOficinaByUUid(enHexa);
    //if()

//""  noC   mal
//aa  noC   mal
//""  SiC   mal
//aa  SiC   biem
    if(!Ofi.isEmpty()  && PSQLConnector->getAccessByUid(enHexa).contains(RcArr.at(7))){
        if(Ofi.at(0) == "X"){

            passNueva = "XXXX";
        }else{
            int num =qrand();
            passNueva =QString::number((num/2)%6)+
                        QString::number((num/3)%6) +
                        QString::number((num/10)%6)+
                        QString::number((num)%6);
        }

        QString estring = ("#v,y," +passNueva+","+ PSQLConnector->getName(enHexa) + "$");
        Port->write(estring.toUtf8());

        if(PSQLConnector->getUbicacionByUid(enHexa) == RcArr.at(7)){
            if(RcArr.at(7) == 'O' ||RcArr.at(7) == 'M'||RcArr.at(7) == 'A'){
                //Entrando al Hall
                PSQLConnector->setUbicacionByUid(enHexa,"H");
                PSQLConnector->setMovimientosUsuario(enHexa, 'H');
            }else{
                //Saliendo del edifico
                PSQLConnector->setUbicacionByUid(enHexa,"A");
                PSQLConnector->setMovimientosUsuario(enHexa, 'A');
            }
        }else{
            //Entrando a la habitacion
            PSQLConnector->setUbicacionByUid(enHexa,QString(QChar::fromLatin1(RcArr.at(7))));
            PSQLConnector->setMovimientosUsuario(enHexa, QString(QChar::fromLatin1(RcArr.at(7))));
        }

        PSQLConnector->setPasswordByUid(enHexa,passNueva );
        ui->plainTextEdit_2->appendPlainText(estring);
        ui->plainTextEdit_2->appendPlainText("Bien!");
        ui->plainTextEdit_2->appendPlainText(enHexa);

    }
    else{
        Port->write("#v,N,1233,juan$");
        ui->plainTextEdit_2->appendPlainText("Mal!");
        ui->plainTextEdit_2->appendPlainText(enHexa);

    }
}

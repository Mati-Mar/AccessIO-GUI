#include "edificiopage.h"
#include "ui_edificiopage.h"

EdificioPage::EdificioPage(QWidget *parent, QSerialPort* Port, PostgreSQLConnector* PSQLConnector) :
    QWidget(parent),
    ui(new Ui::EdificioPage),
    Port(Port),
    PSQLConnector(PSQLConnector)
{
    isUartConnectedFlag = (Port != nullptr);
    initEdificioPage();
}

EdificioPage::~EdificioPage()
{
    if (PSQLConnector->isOpen())
        PSQLConnector->cerrarConexionBD();
    delete Port;
    delete ui;
}

void EdificioPage::initEdificioPage () {
    ui->setupUi(this);
    this->setFixedSize(1000, 600);

    QPixmap pix(":/img/accessio_logo.png");
    QPixmap pixSalas(":/img/Salas.png");
    ui->logoLabel->setPixmap(pix.scaled(ui->logoLabel->width(),
                                        ui->logoLabel->height(),
                                        Qt::KeepAspectRatio));
    ui->salasLabel->setPixmap(pixSalas.scaled(ui->salasLabel->width(),
                                              ui->salasLabel->height(),
                                              Qt::KeepAspectRatio));
    usuariosInsideBuildingCounter();
}

void EdificioPage::usuariosInsideBuildingCounter( void ) {


    unsigned int contadorOficinas = PSQLConnector->getUsuariosInRoom("O");
    unsigned int contadorMaquinas = PSQLConnector->getUsuariosInRoom("M");
    unsigned int contadorHall = PSQLConnector->getUsuariosInRoom("H");

    ui->oficinasCounterLabel->setText(QString::number(contadorOficinas));
    ui->maquinasCounterLabel->setText(QString::number(contadorMaquinas));
    ui->hallCounterLabel->setText(QString::number(contadorHall));
    ui->totalCounterLabel->setText(QString::number(contadorHall + contadorMaquinas + contadorOficinas ));
}

void EdificioPage::on_reloadPushButton_clicked()
{
    usuariosInsideBuildingCounter();
}


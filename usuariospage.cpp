#include "usuariospage.h"
#include "ui_usuariospage.h"

UsuariosPage::UsuariosPage(QWidget *parent, QSerialPort* Port, PostgreSQLConnector* PSQLConnector) :
    QWidget(parent),
    ui(new Ui::UsuariosPage),
    Port(Port),
    PSQLConnector(PSQLConnector)
{
    ui->setupUi(this);
    initUsuariosPage();
}

UsuariosPage::~UsuariosPage()
{
    delete ui;
}

void UsuariosPage::initUsuariosPage( void ) {
    QPixmap pix(":/img/accessio_logo.png");
    ui->logoLabel->setPixmap(pix.scaled(ui->logoLabel->width(),
                                        ui->logoLabel->height(),
                                        Qt::KeepAspectRatio));
}

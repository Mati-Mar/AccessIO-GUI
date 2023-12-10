#include "usuariospage.h"
#include "ui_usuariospage.h"
#include <QMessageBox>

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
    if (PSQLConnector->isOpen())
        PSQLConnector->cerrarConexionBD();
    delete Port;
    delete ui;
}

void UsuariosPage::initUsuariosPage( void ) {
    QPixmap pix(":/img/accessio_logo.png");
    ui->logoLabel->setPixmap(pix.scaled(ui->logoLabel->width(),
                                        ui->logoLabel->height(),
                                        Qt::KeepAspectRatio));
}

void UsuariosPage::on_Commit_clicked()
{
        QString Acceso = ui->AccesosInp->toPlainText();
        QString Nombre = ui->NombreInp->toPlainText();
        QString Apellido = ui->ApellidoInp->toPlainText();
        QString Edad = ui->EdadInp->toPlainText();
          QString Oficina= ui->OficinaInp->toPlainText();

    if(Acceso.isEmpty()|| Nombre.isEmpty()|| Apellido.isEmpty() ||Edad.isEmpty() ||Oficina.isEmpty()){
        QMessageBox::critical(this,"Error",QString::fromLatin1("Faltan campos por rellenar!"));

        return;
    }

    if(PSQLConnector->ExistOficinaId(Oficina))
    {
        QMessageBox::critical(this,"Error",QString::fromLatin1("Esta Oficina ya esta ocupada!"));

        return;
    }
    QString estring;
    estring += "#";
    Port->write("#Add$");
}


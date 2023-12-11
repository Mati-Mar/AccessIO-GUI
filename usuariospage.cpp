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
void UsuariosPage::recieveUID(QString uidd){

    if(PSQLConnector->existUserByUid(uidd)){
        QMessageBox::critical(this,"Error",QString::fromLatin1("Este usuario ya existe"));
        return;
    }else{

        QMessageBox::about(this,"Aceptar",QString::fromLatin1("El usuario ha sido creado"));
        //QMessageBox::about()

        PSQLConnector->CreateUser(uidd,Acceso,Nombre,Apellido,Edad,Oficina);
    }

    uid.clear();
    Acceso.clear();
    Nombre.clear();
    Apellido.clear();
    Edad.clear();
    Oficina.clear();




}


void UsuariosPage::on_Commit_clicked()
{       uid.clear();
        Acceso.clear();
        Nombre.clear();
        Apellido.clear();
        Edad.clear();
        Oficina.clear();

        Acceso = ui->AccesosInp->toPlainText();
        Nombre = ui->NombreInp->toPlainText();
        Apellido = ui->ApellidoInp->toPlainText();
        Edad = ui->EdadInp->toPlainText();
        Oficina= ui->OficinaInp->toPlainText();

    if(Acceso.isEmpty()|| Nombre.isEmpty()|| Apellido.isEmpty() ||Edad.isEmpty() ||Oficina.isEmpty()){
        QMessageBox::critical(this,"Error",QString::fromLatin1("Faltan campos por rellenar!"));

        return;
    }

    if(PSQLConnector->ExistOficinaId(Oficina) && !Oficina.contains("X"))
    {

        QMessageBox::critical(this,"Error",QString::fromLatin1("Esta Oficina ya esta ocupada!"));

        return;
    }
    Port->write("#Add$");
    QMessageBox::about(this,"Aceptar",QString::fromLatin1("Ingrese su tarjeta en el sensor"));

}


void UsuariosPage::on_Commit_2_clicked()
{
    if(PSQLConnector->existUserByUid(ui->EliminarInp->toPlainText())){
        PSQLConnector->deleteUserByUid(ui->EliminarInp->toPlainText());
        QMessageBox::about(this,"Aceptar",QString::fromLatin1("El usuario ha sido eliminado"));

        ui->EliminarInp->clear();
    }
    else
        QMessageBox::critical(this,"Error",QString::fromLatin1("este usuario no existe!"));

}


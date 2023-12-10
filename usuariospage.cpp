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
    }
    ui->plainTextEdit->appendPlainText("La uid es: ");
    ui->plainTextEdit->appendPlainText(uidd);

    PSQLConnector->CreateUser(uidd,Acceso,Nombre,Apellido,Edad,Oficina);


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

    if(PSQLConnector->ExistOficinaId(Oficina))
    {
        QMessageBox::critical(this,"Error",QString::fromLatin1("Esta Oficina ya esta ocupada!"));

        return;
    }
    Port->write("#Add$");
}


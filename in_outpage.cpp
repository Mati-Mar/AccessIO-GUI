#include "in_outpage.h"
#include "ui_in_outpage.h"

In_OutPage::In_OutPage(QWidget *parent, QSerialPort* Port, PostgreSQLConnector* PSQLConnector) :
    QWidget(parent),
    ui(new Ui::In_OutPage),
    Port(Port),
    PSQLConnector(PSQLConnector)
{
    ui->setupUi(this);
    initIn_OutPage();
}

In_OutPage::~In_OutPage()
{
    delete ui;
}

void In_OutPage::initIn_OutPage( void ) {
    QPixmap pix(":/img/accessio_logo.png");
    QPixmap lupaPix(":/img/lupa.png");
    ui->logoLabel->setPixmap(pix.scaled(ui->logoLabel->width(),
                                        ui->logoLabel->height(),
                                        Qt::KeepAspectRatio));
    ui->lupaLabel->setPixmap(lupaPix.scaled(ui->lupaLabel->width(),
                                        ui->lupaLabel->height(),
                                        Qt::KeepAspectRatio));

    if (!PSQLConnector->isOpen())
        PSQLConnector->abrirConexionBD();

    //QSqlTableModel *model = PSQLConnector->getModeloUsuarioLocation();
    //ui->tablaUsuarios->setModel(model);
    //ui->tablaUsuarios->setColumnHidden(model->fieldIndex("id"), true);  // Ocultar la columna "id"
    //ui->tablaUsuarios->show();

}

void In_OutPage::on_buscarUsuariosLineEdit_returnPressed()
{
    QString nombreCompleto = ui->buscarUsuariosLineEdit->text();
    ui->usuarioLabel->setText(nombreCompleto);
    ui->buscarUsuariosLineEdit->setText("");
    QRegExp separator("( )");
    QStringList list = nombreCompleto.split(separator);

    QSqlTableModel *model = PSQLConnector->getModeloUsuarioLocation(nullptr, list.first(), list.last());
    ui->tablaUsuarios->setModel(model);
    ui->tablaUsuarios->setColumnHidden(model->fieldIndex("id"), true);  // Ocultar la columna "id"
    ui->tablaUsuarios->show();



}


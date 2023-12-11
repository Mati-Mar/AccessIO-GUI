#include "in_outpage.h"
#include "ui_in_outpage.h"

#include <QMessageBox>

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
    if (PSQLConnector->isOpen())
        PSQLConnector->cerrarConexionBD();
    delete ui;
}

void In_OutPage::initIn_OutPage( void ) {
    QPixmap pix(":/img/accessio_logo.png");
    ui->logoLabel->setPixmap(pix.scaled(ui->logoLabel->width(),
                                        ui->logoLabel->height(),
                                        Qt::KeepAspectRatio));
    ui->nombreLineEdit->setPlaceholderText("Nombre");
    ui->apellidoLineEdit->setPlaceholderText("Apellido");
    ui->lupaPushButton->setFixedSize(25,25);
    ui->tablaUsuarios->setFixedSize(819, 379);
}

void In_OutPage::on_nombreLineEdit_returnPressed()
{
    if (!ui->apellidoLineEdit->text().isEmpty() && !ui->nombreLineEdit->text().isEmpty())
        formatTablaUsuarios(ui->nombreLineEdit->text(), ui->apellidoLineEdit->text());
    else
        QMessageBox::critical(this,"Campos incompletos",QString::fromLatin1("Ingrese su nombre y apellido"));
}

void In_OutPage::on_apellidoLineEdit_returnPressed()
{
    if (!ui->apellidoLineEdit->text().isEmpty() && !ui->nombreLineEdit->text().isEmpty())
        formatTablaUsuarios(ui->nombreLineEdit->text(), ui->apellidoLineEdit->text());
    else
        QMessageBox::critical(this,"Campos incompletos",QString::fromLatin1("Ingrese su nombre y apellido"));
}

void In_OutPage::on_lupaPushButton_clicked()
{
    if (!ui->apellidoLineEdit->text().isEmpty() && !ui->nombreLineEdit->text().isEmpty())
        formatTablaUsuarios(ui->nombreLineEdit->text(), ui->apellidoLineEdit->text());
    else
        QMessageBox::critical(this,"Campos incompletos",QString::fromLatin1("Ingrese su nombre y apellido"));
}

void In_OutPage::formatTablaUsuarios ( QString nombre, QString apellido ) {
    QString nombreFormateado = nombre.toLower().replace(0, 1, nombre.left(1).toUpper());
    QString apellidoFormateado = apellido.toLower().replace(0, 1, apellido.left(1).toUpper());
    ui->usuarioLabel->setAlignment(Qt::AlignCenter);
    ui->usuarioLabel->setText(QString("%1 %2").arg(nombreFormateado, apellidoFormateado));
    ui->nombreLineEdit->clear();
    ui->apellidoLineEdit->clear();

    QSqlTableModel *model = PSQLConnector->getModeloUsuarioLocation(nullptr, nombreFormateado, apellidoFormateado);
    ui->tablaUsuarios->reset();
    ui->tablaUsuarios->setModel(model);
    ui->tablaUsuarios->setColumnHidden(model->fieldIndex("id"), true);  // Ocultar la columna "id"
    ui->tablaUsuarios->setColumnWidth(1, 260);
    ui->tablaUsuarios->setColumnWidth(2, 260);
    ui->tablaUsuarios->setColumnWidth(3, 260);
    ui->tablaUsuarios->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tablaUsuarios->show();
}

#include "edificiopage.h"
#include "ui_edificiopage.h"

EdificioPage::EdificioPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EdificioPage)
{
    isUartConnectedFlag = false;
    initEdificioPage();
}

EdificioPage::EdificioPage(QWidget *parent, QSerialPort* Port) :
    QWidget(parent),
    ui(new Ui::EdificioPage)
{
    isUartConnectedFlag = (Port);
    initEdificioPage();
}

EdificioPage::~EdificioPage()
{
    delete Port;
    delete ui;
}

void EdificioPage::initEdificioPage () {
    ui->setupUi(this);
    QPixmap pix(":/img/accessio_logo.jpeg");
    ui->logoLabel->setPixmap(pix.scaled(ui->logoLabel->width(),
                                        ui->logoLabel->height(),
                                        Qt::KeepAspectRatio));

    if (isUartConnectedFlag) {
        ui->portLabel->setText("CON CONEXION");
    } else {
        ui->portLabel->setText("SIN CONEXION");
    }

}

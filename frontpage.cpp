#include "frontpage.h"
#include "ui_frontpage.h"
#include <QPixmap>

FrontPage::FrontPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FrontPage)
{
    initFrontpage();
}

FrontPage::FrontPage(QWidget *parent, QString portname) :
    QMainWindow(parent),
    ui(new Ui::FrontPage)
{
    initFrontpage();
    ui->portLabel->setText(portname);
}

void FrontPage::initFrontpage() {
    ui->setupUi(this);
    QPixmap pix(":/img/accessio_logo.jpeg");
    int w = ui->logoLabel->width();
    int h = ui->logoLabel->height();
    ui->logoLabel->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

FrontPage::~FrontPage()
{
    delete ui;
}

void FrontPage::on_edificioPushButton_clicked()
{

}

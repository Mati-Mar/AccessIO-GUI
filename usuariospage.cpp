#include "usuariospage.h"
#include "ui_usuariospage.h"

UsuariosPage::UsuariosPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UsuariosPage)
{
    ui->setupUi(this);
}

UsuariosPage::~UsuariosPage()
{
    delete ui;
}

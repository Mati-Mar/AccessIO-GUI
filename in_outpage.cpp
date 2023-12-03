#include "in_outpage.h"
#include "ui_in_outpage.h"

In_OutPage::In_OutPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::In_OutPage)
{
    ui->setupUi(this);
}

In_OutPage::~In_OutPage()
{
    delete ui;
}

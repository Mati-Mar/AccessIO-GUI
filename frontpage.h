#ifndef FRONTPAGE_H
#define FRONTPAGE_H

#include <QMainWindow>
#include <QSerialPort>

#include "postgresqlconnector.h"

namespace Ui {
class FrontPage;
}

class FrontPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit FrontPage(QWidget *parent = nullptr);
    //FrontPage(QWidget *parent = nullptr, QSerialPort port);
    explicit FrontPage(QWidget *parent = nullptr, QString portname = "");
    ~FrontPage();
    bool isUartConnectedFlag;



    QString getPortname() const;
    void setPortname(const QString &newPortname);

private slots:
    void on_edificioPushButton_clicked();

private:
    Ui::FrontPage *ui;
    QSerialPort *Port;
    QString portname;
    void initPort(QString portname);
    void initFrontpage();
    void abrirEdificioPage();
    void abrirUsuariosPage();
    void abrirIn_OutPage();
};

#endif // FRONTPAGE_H

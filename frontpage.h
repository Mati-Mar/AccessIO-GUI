#ifndef FRONTPAGE_H
#define FRONTPAGE_H

#include <QMainWindow>
#include <QSerialPort>
#include <QByteArray>

#include "postgresqlconnector.h"

namespace Ui {
class FrontPage;
}

class FrontPage : public QMainWindow
{
    Q_OBJECT

public:
    void recieve(QString Rx);
    explicit FrontPage(QWidget *parent = nullptr);
    explicit FrontPage(QWidget *parent = nullptr, QString portname= "");
    ~FrontPage();
    bool isUartConnectedFlag;
    QString getPortname() const;
    void setPortname(const QString &newPortname);

private slots:
    void on_edificioPushButton_clicked();
    void on_Port_rx();
    void on_usuariosPushButton_clicked();

    void on_inoutPushButton_clicked();

private:
    void handlePas(QByteArray RcArr);

    Ui::FrontPage *ui;
    QSerialPort *Port;
    QString portname;
    QByteArray RcArr;
    PostgreSQLConnector * PSQLConnector;
    void initPort(QString portname);
    void initFrontpage();
    void abrirEdificioPage();
    void abrirUsuariosPage();
    void abrirIn_OutPage();
};

#endif // FRONTPAGE_H

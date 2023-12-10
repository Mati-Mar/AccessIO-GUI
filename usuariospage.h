#ifndef USUARIOSPAGE_H
#define USUARIOSPAGE_H

#include <QWidget>
#include <QSerialPort>

#include "postgresqlconnector.h"

namespace Ui {
class UsuariosPage;
}

class UsuariosPage : public QWidget
{
    Q_OBJECT

public:
    explicit UsuariosPage(QWidget *parent = nullptr,
                          QSerialPort* Port = nullptr,
                          PostgreSQLConnector* PSQLConnector = nullptr);
    ~UsuariosPage();
    void recieveUID(QString uidd);

private slots:
    void on_Commit_clicked();

private:
    QString uid;
    QString Acceso;
    QString Nombre;
    QString Apellido;
    QString Edad;
    QString Oficina;
    Ui::UsuariosPage *ui;
    void initUsuariosPage( void );

    QSerialPort *Port;
    PostgreSQLConnector * PSQLConnector;
};

#endif // USUARIOSPAGE_H
